-- 177. 第N高的薪水

-- https://leetcode-cn.com/problems/nth-highest-salary/

CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
  DECLARE a INT DEFAULT 0;
  SET a = N - 1;
  RETURN (
    SELECT IFNULL((SELECT DISTINCT Salary
                   FROM Employee
                   ORDER BY Salary DESC
                   LIMIT a,1), NULL));
END
