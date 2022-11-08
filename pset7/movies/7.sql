SELECT m.title, r.rating
FROM (SELECT * FROM movies WHERE movies.year=2010) AS m
JOIN ratings AS r ON m.id=r.movie_id
ORDER BY rating DESC, title;