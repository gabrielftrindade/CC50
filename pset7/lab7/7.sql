-- 7.sql: retorna a energia média das músicas de Drake
SELECT AVG(energy)
FROM songs
WHERE artist_id = (SELECT id
FROM artists
WHERE name = "Drake");