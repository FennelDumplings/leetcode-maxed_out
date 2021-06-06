-- 183. 从不订购的客户

-- https://leetcode-cn.com/problems/customers-who-never-order/

SELECT c.Name AS Customers
FROM Customers AS c
WHERE c.Id NOT IN (
    SELECT CustomerId
    FROM Orders
)

SELECT c.Name AS Customers
FROM Customers AS c LEFT JOIN Orders AS o
ON c.Id = o.CustomerId
WHERE o.CustomerId IS NULL
