# Copyright (c) 2008 Pluron, Inc.

require 'array_diff'

module AssertSame

class TextDiff

    def self.mapped_chunk(arr, from, to)
        return [] if to < from
        arr[from, to-from+1].map{|x| [' ', x]}
    end

    def self.chunk(arr, from, to)
        result = []
        if to - from > 2
            result += self.mapped_chunk(arr, from, from+2) if from > 0
            result << ['@', to-2]
            result += self.mapped_chunk(arr, to-2, to)
        else 
            result << ['@', from] if from == 0
            result += self.mapped_chunk(arr, from, to)
        end
    end

    def self.record_stat(arr, at, remcount, addcount, linecount, offset)
        index = arr[at][1]+1
        ['', "@@ -#{index},#{linecount-addcount}, +#{index+offset},#{linecount-remcount} @@"]
    end

    def self.diff(a_text, b_text)
        a = a_text.split("\n")
        b = b_text.split("\n")
        self.array_diff(a, b)
    end

    def self.array_diff(a, b)
        diff = ArrayDiff.new(a, b)

        return nil if diff.diffs.empty?

        result = []

        from = to = nextfrom = 0
        offset = 0
        diff.diffs.each do |tuple|
            first = tuple[0][1]
            length = tuple.length
            action = tuple[0][0]
            addcount = 0
            remcount = 0
            tuple.each do |l| 
                if l[0] == "+"
                    addcount += 1
                elsif l[0] == "-"
                    remcount += 1
                end
            end
            if remcount == 0
                to = first-offset-1
                nextfrom = to+1
            else
                to = first-1
                nextfrom = to+remcount+1
            end
            result += self.chunk(a, from, to)
            from = nextfrom
            lastdel = (tuple[0][0] == "-")
            tuple.each do |l|
                if l[0] == "-"
                    offset -= 1
                else
                    offset += 1
                end
                result << [l[0], l[2]]
            end
        end
        if (a.length - from) > 2
            result += self.chunk(a, from, from+2)
        elsif a.length > 0
            result += self.chunk(a, from, a.length-1)
        end
        linecount = addcount = remcount = offset = current_offset = 0
        info_index = nil
        result.each_with_index do |l, i|
            if l[0] == '@'
                result[info_index] = self.record_stat(result, info_index, remcount, addcount, 
                    linecount, offset) if info_index
                info_index = i
                offset += addcount - remcount
                linecount = 0
                addcount = remcount = 0
            elsif l[0] == '-'
                remcount += 1
                linecount += 1
            elsif l[0] == '+'
                addcount += 1
                linecount += 1
            else
                linecount += 1
            end
        end
        result[info_index] = self.record_stat(result, info_index, remcount, addcount, linecount, offset) if info_index
        return result.map{|x| x.join('')}.join("\n")
    end

end

end
