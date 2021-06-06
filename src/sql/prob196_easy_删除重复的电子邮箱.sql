-- 196. 删除重复的电子邮箱

-- https://leetcode-cn.com/problems/delete-duplicate-emails/

DELETE FROM Person
WHERE Id NOT IN (
    SELECT MIN(tmp.Id) AS Id
    FROM (SELECT * FROM Person) tmp
    GROUP BY tmp.Email
    )
