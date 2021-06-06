-- 181. 超过经理收入的员工

-- https://leetcode-cn.com/problems/employees-earning-more-than-their-managers/

SELECT t1.Name AS Employee
FROM Employee AS t1, Employee AS t2
WHERE t1.ManagerId = t2.Id
    AND t1.Salary > t2.Salary


SELECT t1.Name AS Employee
FROM Employee AS t1 JOIN Employee AS t2
ON t1.ManagerId = t2.Id
    AND t1.Salary > t2.Salary
