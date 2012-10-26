{% load kdev_filters %}
#

{{ license|lines_prepend:"# " }}
#


class {{ name }}

    {% for method in methods %}
    def {{ method.name }}
    end
    {% endfor %}

end
