# coding: UTF-8

Gem::Specification.new do |s|
  s.name              = "%{APPNAMELC}"
  s.version           = "0.0.1"
  s.platform          = Gem::Platform::RUBY
  s.authors           = ["Author's name"]
  s.email             = ["author at example dot com"]
  s.summary           = "WARNING: Update the summary"
  s.description       = "WARNING: Update the description"
  s.required_rubygems_version = ">= 1.3.6"

  # The list of files to be contained in the gem
  s.files         = ['Rakefile', '%{APPNAMELC}.gemspec', 'Gemfile',
                    'test/test_helper.rb', 'lib/%{APPNAMELC}.rb']
  s.require_path = 'lib'
end
