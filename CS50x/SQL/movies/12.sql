-- Find BC ID
-- Find JL ID
-- Find BC movies
-- Find JL movies
-- Find titles shared between the two
SELECT title
FROM movies
JOIN stars
ON movies.id = stars.movie_id
WHERE stars.movie_id
IN
(
    SELECT movie_id
    FROM stars
    WHERE person_id IN
    (
        SELECT id
        FROM people
        WHERE name = 'Bradley Cooper'
    )
)
AND movies.id
IN
(
    SELECT movie_id
    FROM stars
    WHERE person_id IN
    (
        SELECT id
        FROM people
        WHERE name = 'Jennifer Lawrence'
    )
)
;
