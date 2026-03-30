-- Q1
CREATE TRIGGER trg_player_after_insert
ON player
AFTER INSERT
AS
BEGIN
    PRINT 'New player has been added.';
END;
GO


-- Q2
CREATE TRIGGER trg_team_after_delete
ON team
AFTER DELETE
AS
BEGIN
    SELECT 'Deleted Team: ' + tname AS Message
    FROM deleted;
END;
GO


-- Q3
CREATE TRIGGER trg_player_salary_update
ON player
AFTER UPDATE
AS
BEGIN
    IF UPDATE(salary)
    BEGIN
        PRINT 'Player salary updated.';
    END
END;
GO


-- Q4
CREATE TRIGGER trg_player_instead_insert
ON player
INSTEAD OF INSERT
AS
BEGIN
    IF EXISTS (SELECT 1 FROM inserted WHERE age < 16)
    BEGIN
        PRINT 'Insertion blocked: Age must be >= 16';
    END
    ELSE
    BEGIN
        INSERT INTO player (pname, pid, age, role, salary, tid, captain_id)
        SELECT pname, pid, age, role, salary, tid, captain_id
        FROM inserted;
    END
END;
GO


-- Q5
ALTER TABLE player
ADD total_runs INT DEFAULT 0,
    total_wickets INT DEFAULT 0;
GO

CREATE TRIGGER trg_performance_after_insert
ON performance
AFTER INSERT
AS
BEGIN
    UPDATE p
    SET 
        p.total_runs = p.total_runs + i.runs,
        p.total_wickets = p.total_wickets + i.wickets
    FROM player p
    JOIN inserted i ON p.pid = i.pid;
END;
GO


-- Q6
CREATE TRIGGER trg_team_after_delete_players
ON team
AFTER DELETE
AS
BEGIN
    DELETE FROM player
    WHERE tid IN (SELECT tid FROM deleted);
END;
GO


-- Q7
CREATE TRIGGER trg_match_winner_update
ON match
AFTER UPDATE
AS
BEGIN
    IF UPDATE(winner_id)
    BEGIN
        IF EXISTS (
            SELECT 1
            FROM inserted i
            JOIN deleted d ON i.mid = d.mid
            WHERE i.winner_id <> d.winner_id
        )
        BEGIN
            PRINT 'Match winner has been changed.';
        END
    END
END;
GO


-- Q8
CREATE TRIGGER trg_player_instead_delete
ON player
INSTEAD OF DELETE
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM deleted d
        JOIN performance p ON d.pid = p.pid
    )
    BEGIN
        PRINT 'Cannot delete player with performance records.';
    END
    ELSE
    BEGIN
        DELETE FROM player
        WHERE pid IN (SELECT pid FROM deleted);
    END
END;
GO


-- Q9
CREATE TRIGGER trg_performance_after_insert_multi
ON performance
AFTER INSERT
AS
BEGIN
    DECLARE @total_runs INT;

    SELECT @total_runs = SUM(runs) FROM inserted;

    PRINT 'Total runs added: ' + CAST(@total_runs AS VARCHAR);
END;
GO


-- Q10
CREATE TABLE audit_salary (
    audit_id INT IDENTITY(1,1) PRIMARY KEY,
    pid INT,
    old_salary DECIMAL(10,2),
    new_salary DECIMAL(10,2),
    change_date DATETIME DEFAULT GETDATE()
);
GO

CREATE TRIGGER trg_player_salary_audit
ON player
AFTER UPDATE
AS
BEGIN
    IF UPDATE(salary)
    BEGIN
        INSERT INTO audit_salary (pid, old_salary, new_salary)
        SELECT 
            d.pid,
            d.salary,
            i.salary
        FROM deleted d
        JOIN inserted i ON d.pid = i.pid
        WHERE d.salary <> i.salary;
    END
END;
GO