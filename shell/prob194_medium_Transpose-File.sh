# prob194: Transpose File

# Given a text file file.txt, transpose its content.
# You may assume that each row has the same number of columns and each field is separated by the ' ' character.


# Example:
# 
# If file.txt has the following content:
# 
#     name age
#     alice 21
#     ryan 30
#     Output the following:
# 
#     name alice ryan
#     age 21 30


awk '{
    for (i=1; i<=NF; i++){
        if(NR==1){
            res[i]=$i;
        }
        else{
            res[i]=res[i] " " $i
        }
    }
}
END{
    for (i=1; i<=NF; i++){
        print res[i]
    }
}' file.txt
