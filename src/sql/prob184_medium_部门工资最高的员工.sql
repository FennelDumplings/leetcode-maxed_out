-- 184. 部门工资最高的员工

-- https://leetcode-cn.com/problems/department-highest-salary/

SELECT d.Name AS Department, e.Name AS Employee, e.Salary AS Salary
FROM Employee AS e INNER JOIN Department AS d
ON e.DepartmentId = d.Id
WHERE (e.DepartmentId, e.Salary) IN (
    SELECT DepartmentId, MAX(Salary)
    FROM Employee
    GROUP BY DepartmentId
    )

SELECT department, employee, salary
FROM (
    SELECT d.name AS Department, e.name AS Employee, e.Salary AS Salary,
        RANK() OVER (PARTITION by e.DepartmentId ORDER BY e.Salary DESC) AS r
    FROM Employee AS e INNER JOIN Department as d
    on e.DepartmentId = d.Id
) t
where r = 1

