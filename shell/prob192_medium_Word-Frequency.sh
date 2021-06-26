# prob192: Word Frequency

# For simplicity sake, you may assume:
# words.txt contains only lowercase characters and space ' ' characters.
# Each word must consist of lowercase characters only.
# Words are separated by one or more whitespace characters.


# Example:
# 
# Assume that words.txt has the following content:
# 
# the day is sunny the the
# the sunny is is
# Your script should output the following, sorted by descending frequency:
# 
# the 4
# is 3
# sunny 2
# day 1
# Note:
# 
# Don't worry about handling ties, it is guaranteed that each word's frequency count is unique.
# Could you write it in one-line using Unix pipes?


cat words.txt | sed 's/\s\+/\n/g' | grep -v '^$' | sort | uniq -c | awk '{print $2" "$1}' | sort -r -n -k 2

awk '{
    for(i = 1; i <= NF; i++){
        res[$i] += 1 #以字符串为索引，res[$i]相同的累计
    }
}
END{
    for(k in res){
        print k" "res[k]
    }
}' words.txt | sort -nr -k2  # n：按数值排序，r：倒序，k：按第2列排序


