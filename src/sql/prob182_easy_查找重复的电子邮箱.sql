-- 182. 查找重复的电子邮箱

-- https://leetcode-cn.com/problems/duplicate-emails/

SELECT Email
FROM Person
GROUP BY Email
HAVING COUNT(Email) > 1

SELECT Email
FROM (
    SELECT *, COUNT(Email) as Cnt
    FROM Person
    GROUP BY Email
) AS t
WHERE Cnt > 1
