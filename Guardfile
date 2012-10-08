##
# This file is part of KDevelop
#
# Copyright (C) 2012 Miquel Sabaté <mikisabate@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.


require 'guard'
require 'guard/guard'


module ::Guard
  # Subclass the Guard::Guard class so then we can setup the watchers
  # through the guard('kdev') method call.
  class KDev < ::Guard::Guard
    # Public: Initialize the Guard::KDev watcher.
    #
    # watchers - an Array containing the Guard watchers.
    # options  - a Hash with the available options:
    #            :build_url - a String representing the absolute path to the
    #                         build dir.
    #            :tests     - an Array of hashes with the config for each test.
    def initialize(watchers = [], options = {})
      super
      @opts = { :build_url => '', :tests => [] }.merge(options)
    end

    # Public: It will be called on start. It just shows a message.
    #
    # Returns nothing.
    def start
      UI.info "Watching everything inside: #{@opts[:build_url]}"
    end

    # Public: It will be called when some watched file has changed. It runs
    # all the tests again.
    #
    # paths - An Array containing the path of the files that have changed.
    #
    # Returns nothing.
    def run_on_changes(paths)
      run_all
    end

    # Public: Run all the tests and notify the user (console and libnotify).
    #
    # Returns nothing.
    def run_all
      @results = []
      @failed = 0
      @opts[:tests].each do |t|
        name = t[:url].match(/^\w+\//)[0].chop.capitalize
        UI.info "Running tests for #{name}..."
        t[:execs] = [t[:execs]] if t[:execs].is_a? String
        run_tests name, t[:url], t[:execs]
      end

      notify!
    end

    private

    # Internal: Run all the tests of a certain component.
    #
    # name  - A String with the name of the component.
    # url   - A String with the relative url of the component's test directory.
    # tests - An Array of strings where each string is the command to be
    #         executed in order to run the test.
    #
    # Returns nothing.
    def run_tests(name, url, tests)
      base = @opts[:build_url] + url
      tests.each do |t|
        UI.info "Executing the following command: '#{t}' in #{base}"
        Dir.chdir base
        output = `#{t}`
        append_results name, output, t.start_with?('./')
      end
    end

    # Internal: Append the results of an execution to the @results array.
    #
    # name       - A String with the name of the component.
    # text       - A String with the output of the execution.
    # executable - A Boolean that tells us whether this execution comes from
    #              an executable file or not.
    #
    # Returns nothing.
    def append_results(name, text, executable)
      total, win = 0, 0
      if executable
        text.match /Totals: (\d+) passed, (\d+) failed/
        total, win = $1.to_i + $2.to_i, $1.to_i
      else
        line = text.split("\n").last
        line.match /^(\d+) tests, (\d+) assertions/
        total, win = $1.to_i, $2.to_i
      end
      @failed = total - win
      @results << "#{name} -> OK: #{win}, Failed: #{@failed}"
    end

    # Internal: Notify the user by printing the results to the console.
    # A notification will also be sent (i.e. through libnotify).
    #
    # Returns nothing.
    def notify!
      puts "\n************************************************"
      @results.each { |r| puts r }
      puts "************************************************\n"
      if @failed > 0
        ::Guard::Notifier.notify('Some tests are failing !', :image => :failed)
      else
        ::Guard::Notifier.notify('All tests passed !')
      end
    end
  end
end


#
# And now let's use the infrastructure created above :)
#

# The base build url.
build_url = File.join File.expand_path(File.dirname(__FILE__)), ARGV.last
build_url += '/' unless build_url.end_with? '/'

# For each component (Completion, Parser, DUChain) specify the relative url
# and how to execute each test.
cp = { :url => 'completion/tests/', :execs => './completion' }
duchain = { :url => 'duchain/tests/', :execs => ['./duchain', './uses'] }

# Setting up the Guard::KDev watcher for DUChain and CodeCompletion.
guard 'kdev', :build_url => build_url, :tests => [cp, duchain] do
  watch /.*/
end

# And now let's turn the Guard::RSpec watcher on for the parser.
rspec_paths = File.join(ARGV.last, 'parser/tools')
guard 'rspec', :cli => '-c -f doc', :spec_paths => rspec_paths do
  watch(/parser\/(.*)$/) { "#{rspec_paths}/parser_spec.rb" }
end
