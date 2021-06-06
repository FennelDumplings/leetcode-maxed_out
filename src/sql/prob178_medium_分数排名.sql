-- 178. 分数排名

-- https://leetcode-cn.com/problems/rank-scores/

SELECT Score,
    DENSE_RANK() OVER(ORDER BY Score DESC) AS 'Rank'
FROM Scores
