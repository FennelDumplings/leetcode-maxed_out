-- 180. 连续出现的数字

-- https://leetcode-cn.com/problems/consecutive-numbers/

SELECT DISTINCT l1.num AS ConsecutiveNums
FROM Logs AS l1
    ,Logs AS l2
    ,Logs AS l3
WHERE l1.id + 1 = l2.id
    AND l2.id + 1 = l3.id
    AND l1.num = l2.num
    AND l2.num = l3.num

SELECT DISTINCT Num AS ConsecutiveNums
FROM (
    SELECT *,
        ROW_NUMBER() OVER(PARTITION BY Num ORDER BY Id) As 'Rownum',
        ROW_NUMBER() OVER (ORDER BY Id) Id2
    FROM Logs
    ) AS t
GROUP BY (Id2 + 1 - Rownum), Num
HAVING COUNT(*)>=3
