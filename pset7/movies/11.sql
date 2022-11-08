SELECT Chad_movies.title
FROM
    (SELECT m.title, m.id
    FROM movies AS m
        JOIN
            (SELECT s.movie_id, s.person_id
            FROM stars AS s
            WHERE s.person_id=
                (SELECT id
                FROM people
                WHERE name="Chadwick Boseman"))
        ON movie_id = m.id) AS Chad_movies
JOIN ratings AS r
ON Chad_movies.id = r.movie_id
ORDER BY rating DESC
LIMIT 5;
