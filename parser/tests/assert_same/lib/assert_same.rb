# Copyright (c) 2010-2011 Pluron, Inc.
require 'test/unit'
require 'text_diff'

class Test::Unit::TestCase

    #Hash[filename][line_number] = offset
    #For each line in the original file we store its offset (+N or -N lines)
    #relative to the actual file
    @@file_offsets = Hash.new { |hash, key| hash[key] = {} }

    # assert_same: assert which checks that two strings (expected and actual) are same
    # and which can "magically" replace expected value with the actual in case
    # the new behavior (and new actual value) is correct
    #
    # == Usage ==
    #
    # Write this in the test source:
    #     assert_same something, <<-END
    #         foo
    #         bar
    #         zee
    #     END
    # 
    # Then run tests as usual:
    #    rake test:units
    #    ruby test/unit/foo_test.rb
    #    ...
    #
    # When assert_same fails, you'll be able to:
    # - review diff
    # - (optionally) accept new actual value (this modifies the test source file)
    #
    # Additional options for test runs:
    # --no-interactive skips all questions and just reports failures
    # --autoaccept prints diffs and automatically accepts all new actual values
    # --no-canonicalize turns off expected and actual value canonicalization (see below for details)
    #
    # Additional options can be passed during both single test file run and rake test run:
    #    ruby test/unit/foo_test.rb -- --autoaccept
    #    ruby test/unit/foo_test.rb -- --no-interactive
    #
    #    rake test TESTOPTS="-- --autoaccept"
    #    rake test:units TESTOPTS="-- --no-canonicalize --autoaccept"
    #
    #
    #
    # == Canonicalization ==
    #
    # Before comparing expected and actual strings, assert_same canonicalizes both using these rules:
    # - indentation is ignored (except for indentation
    #   relative to the first line of the expected/actual string)
    # - ruby-style comments after "#" are ignored: 
    #   both whole-line and end-of-line comments are supported
    # - empty lines are ignored
    # - trailing whitespaces are ignored
    #
    # You can turn canonicalization off with --no-canonicalize option. This is useful
    # when you need to regenerate expected test strings.
    # To regenerate the whole test suite, run:
    #    rake test TESTOPTS="-- --no-canonicalize --autoaccept"
    #
    # Example of assert_same with comments:
    #  assert_same something, <<-END
    #      # some tree
    #      foo 1
    #        foo 1.1
    #        foo 1.2    # some node
    #      bar 2
    #        bar 2.1
    #  END
    #
    #
    #
    # == Umportant Usage Rules ==
    #
    # Restrictions:
    # - only END and EOS are supported as end of string sequence
    # - it's a requirement that you have <<-END at the same line as assert_same
    # - assert_same can't be within a block
    #
    # Storing expected output in files:
    # - assert_same something, :log => <path_to_file>
    # - path to file is relative to:
    #   - RAILS_ROOT (if that is defined)
    #   - current dir (if no RAILS_ROOT is defined)
    # - file doesn't have to exist, it will be created if necessary
    #
    # Misc:
    # - it's ok to have several assert_same's in the same test method, assert_same.
    #   correctly updates all assert_same's in the test file
    # - it's ok to omit expected string, like this:
    #       assert_same something
    #   in fact, this is the preferred way to create assert_same tests - you write empty
    #   assert_same, run tests and they will fill expected values for you automatically
    def assert_same(actual, expected = :autofill_expected_value)
        if expected.class == String
            expected ||= ""
            mode = :expecting_string
        elsif expected == :autofill_expected_value
            expected = ""
            mode = :autofill_expected_value
        elsif expected.class == Hash
            raise ":log key is missing" unless expected.has_key? :log
            mode = :expecting_file
            log_file = expected[:log]
            if defined? RAILS_ROOT
                log_file = File.expand_path(log_file, RAILS_ROOT)
            else
                log_file = File.expand_path(log_file, Dir.pwd)
            end
            expected = File.exists?(log_file) ? File.read(log_file) : ""
        else
            internal_error("Incorrect expected argument for assert_same. It must be either String or Hash.")
        end

        # interactive mode is turned on by default, except when
        # - --no-interactive is given
        # - STDIN is not a terminal device (i.e. we can't ask any questions)
        interactive = !ARGV.include?("--no-interactive") && STDIN.tty?
        canonicalize = !ARGV.include?("--no-canonicalize")
        autoaccept = ARGV.include?("--autoaccept")

        is_same_canonicalized, is_same, diff_canonicalized, diff = compare_for_assert_same(expected, actual)

        if (canonicalize and !is_same_canonicalized) or (!canonicalize and !is_same)
            diff_to_report = canonicalize ? diff_canonicalized : diff
            if interactive
                # print method name and short backtrace
                failure = Test::Unit::Failure.new(name, filter_backtrace(caller(0)), diff_to_report)
                puts "\n#{failure}"

                if autoaccept
                    accept = true
                else
                    print "Accept the new value: yes to all, no to all, yes, no? [Y/N/y/n] (y): "
                    STDOUT.flush
                    response = STDIN.gets.strip
                    accept = ["", "y", "Y"].include? response
                    ARGV << "--autoaccept" if response == "Y"
                    ARGV << "--no-interactive" if response == "N"
                end

                if accept
                    if [:expecting_string, :autofill_expected_value].include? mode
                        accept_string(actual, mode)
                    elsif mode == :expecting_file
                        accept_file(actual, log_file)
                    end
                end
            end
            if accept
                # when change is accepted, we should not report it as a failure because
                # we want the test method to continue executing (in case there're more
                # assert_same's in the method)
                add_assertion
            else
                raise Test::Unit::AssertionFailedError.new(diff_to_report)
            end
        else
            add_assertion
        end
    end

private

    def accept_string(actual, mode)
        file, method, line = get_caller_location(:depth => 3)

        # read source file, construct the new source, replacing everything
        # between "do" and "end" in assert_same's block
        source = File.readlines(RAILS_ROOT + "/" + file)

        # file may be changed by previous accepted assert_same's, adjust line numbers
        offset = @@file_offsets[file].keys.inject(0) do |sum, i|
            line.to_i >= i ? sum + @@file_offsets[file][i] : sum
        end

        expected_text_end_line = expected_text_start_line = line.to_i + offset
        unless mode == :autofill_expected_value
            #if we're autofilling the value, END/EOS marker will not exist
            #(second arg to assert_same is omitted)
            #else we search for it
            expected_text_end_line += 1 while !["END", "EOS"].include?(source[expected_text_end_line].strip)
        end

        expected_length = expected_text_end_line - expected_text_start_line

        # indentation is the indentation of assert_same call + 4
        indentation = source[expected_text_start_line-1] =~ /^(\s+)/ ? $1.length : 0
        indentation += 4

        if mode == :autofill_expected_value
            # add second argument to assert_same if it's omitted
            source[expected_text_start_line-1] = "#{source[expected_text_start_line-1].chop}, <<-END\n"
        end
        source = source[0, expected_text_start_line] +
            actual.split("\n").map { |l| "#{" "*(indentation)}#{l}\n"} +
            (mode == :autofill_expected_value ? ["#{" "*(indentation-4)}END\n"] : [])+
            source[expected_text_end_line, source.length]

        # recalculate line number adjustments
        actual_length = actual.split("\n").length
        actual_length += 1 if mode == :autofill_expected_value  # END marker after actual value
        @@file_offsets[file][line.to_i] = actual_length - expected_length

        source_file = File.open(RAILS_ROOT + "/" + file, "w+")
        source_file.write(source)
        source_file.fsync
        source_file.close
    end

    def accept_file(actual, log_file)
        log = File.open(log_file, "w+")
        log.write(actual)
        log.fsync
        log.close
    end

    def compare_for_assert_same(expected_verbatim, actual_verbatim)
        expected_canonicalized, expected = canonicalize_for_assert_same(expected_verbatim)
        actual_canonicalized, actual = canonicalize_for_assert_same(actual_verbatim)
        diff_canonicalized = AssertSame::TextDiff.array_diff(expected_canonicalized, actual_canonicalized)
        diff = AssertSame::TextDiff.array_diff(expected, actual)
        [expected_canonicalized == actual_canonicalized, expected == actual, diff_canonicalized, diff]
    end

    def canonicalize_for_assert_same(text)
        # make array of lines out of the text
        result = text.split("\n")

        # ignore leading newlines if any (trailing will be automatically ignored by split())
        result.delete_at(0) if result[0] == ""

        indentation = $1.length if result[0] and result[0] =~ /^(\s+)/

        result.map! do |line|
            # ignore indentation: we assume that the first line defines indentation
            line.gsub!(/^\s{#{indentation}}/, '') if indentation
            # ignore trailing spaces
            line.gsub(/\s*$/, '')
        end

        # ignore comments
        result_canonicalized= result.map do |line|
            line.gsub(/\s*(#.*)?$/, '')
        end
        # ignore blank lines (usually they are lines with comments only)
        result_canonicalized.delete_if { |line| line.nil? or line.empty? }

        [result_canonicalized, result]
    end

end
