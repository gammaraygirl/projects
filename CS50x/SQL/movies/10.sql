--all people who have directed a movie the got a 9.0 or higher rating
-- find all movies that got a 9.0+ rating
-- find the people who directed those
SELECT name
FROM people
WHERE people.id IN
(
    SELECT directors.person_id
    FROM directors
    JOIN movies ON directors.movie_id = movies.id
    JOIN ratings ON movies.id = ratings.movie_id
    WHERE
    rating >= 9.0
)
;

