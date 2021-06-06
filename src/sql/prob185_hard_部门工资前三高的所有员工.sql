-- 185. 部门工资前三高的所有员工

-- https://leetcode-cn.com/problems/department-top-three-salaries/

SELECT Department, Employee, Salary
FROM (
    SELECT d.Name as Department, e.Name AS Employee, e.Salary AS Salary,
        DENSE_RANK() OVER(PARTITION BY e.DepartmentId ORDER BY e.Salary) AS dr
    FROM Employee as e INNER JOIN Department as d
    ON e.DepartmentId = d.Id
) AS t
WHERE dr < 4
