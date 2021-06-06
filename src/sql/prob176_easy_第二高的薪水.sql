-- 176. 第二高的薪水

-- https://leetcode-cn.com/problems/second-highest-salary/

SELECT IFNULL((SELECT DISTINCT Salary
        FROM Employee
        ORDER BY Salary DESC
        LIMIT 1,1), NULL) AS SecondHighestSalary

SELECT (
    SELECT DISTINCT Salary
    FROM Employee
    ORDER BY Salary DESC
    LIMIT 1 OFFSET 1
) AS SecondHighestSalary
