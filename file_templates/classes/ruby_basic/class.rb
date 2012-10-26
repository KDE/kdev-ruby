{% load kdev_filters %}

#
{{ license|lines_prepend:"# " }}


class {{ name }}{% if base_classes %} < {{ base_classes.0.baseType }}{% endif %}

    {% if members %}

    attr_accessor {% for member in members %}:{{member.name}}{% if not forloop.last %}, {% endif %}{% endfor %}
    {% endif %}

    {% for function in functions %}

    def {{ function.name }}
    end

    {% endfor %}

end
