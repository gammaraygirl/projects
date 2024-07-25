-- find KB id
-- find movies KB starred in
-- find other people who starred in those
SELECT name
FROM people
JOIN stars
ON people.id = stars.person_id
WHERE stars.movie_id
IN
(
    -- Movies KB starred in
    SELECT stars.movie_id
    FROM stars
    WHERE person_id
    IN
    (
        -- Kevin Bacon's ID
        SELECT id
        FROM people
        WHERE name = 'Kevin Bacon'
        AND birth = 1958
    )
)
AND
stars.person_id !=
(
   SELECT id
    FROM people
    WHERE name = 'Kevin Bacon'
    AND birth = 1958
)
;

