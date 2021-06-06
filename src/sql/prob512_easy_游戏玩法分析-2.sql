-- 512. 游戏玩法分析 II

-- https://leetcode-cn.com/problems/game-play-analysis-ii/

SELECT player_id, device_id
FROM Activity
WHERE (player_id, event_date) IN (
    SELECT player_id, MIN(event_date) AS first_login
    FROM Activity
    GROUP BY player_id
    )
