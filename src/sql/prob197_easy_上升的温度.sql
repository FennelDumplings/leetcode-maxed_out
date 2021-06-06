-- https://leetcode-cn.com/problems/rising-temperature/

-- 197. 上升的温度

SELECT w2.ID AS id
FROM Weather AS w1, Weather AS w2
WHERE DATEDIFF(w2.recordDate, w1.recordDate) = 1
    AND w1.Temperature < w2.Temperature
