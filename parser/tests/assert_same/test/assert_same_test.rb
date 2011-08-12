# Copyright (c) 2011 Pluron, Inc.

require 'test/unit'
require 'lib/assert_same'

class AssertSameTest < Test::Unit::TestCase

    def test_basic_assert_same
        assert_same "foo", <<-END
            foo
        END
    end

    def test_assert_same_with_files
        assert_same "foo", :log => 'test/logs/assert_same_with_files.log.ref'
    end

end
