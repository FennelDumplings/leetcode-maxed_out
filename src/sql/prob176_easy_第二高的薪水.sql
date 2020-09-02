-- 176. 第二高的薪水

-- https://leetcode-cn.com/problems/second-highest-salary/

SELECT MAX(Salary) AS SecondHighestSalary
FROM Employee
WHERE Salary != (SELECT max(Salary)
                 FROM Employee);

SELECT IFNULL((SELECT DISTINCT Salary
        FROM Employee
        ORDER BY Salary DESC
        LIMIT 1,1), NULL) AS SecondHighestSalary
