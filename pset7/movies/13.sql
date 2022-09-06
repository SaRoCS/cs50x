SELECT DISTINCT name FROM people JOIN stars ON people.id = stars.person_id WHERE id IN (
SELECT person_id FROM stars WHERE movie_id IN (
SELECT movie_id FROM stars JOIN people ON stars.person_id = people.id WHERE name = "Kevin Bacon" AND birth = 1958))
AND NOT id = (SELECT id FROM people WHERE name = "Kevin Bacon" AND birth = 1958);