
/*
Create a SQL script called 'lab03.sql' that performs the following steps:

1. By introducing the tabletop_games table, having our previous table called games introduces some ambiguity.
		[If you used video_games as the name of your table in Lab 02, determine how you would alter the table to games and then back to video_games.]
		Use the ALTER TABLELinks to an external site. statement to rename the games table to video_games. 
		In Lab 02 we used a foreign key constraint in game_characters based on the primary key in games. Determine whether changing the table name requires you to also alter the foreign key constraint or if it automatically updates.
			Include either the command to update the constraint or an "auto-update" comment in your .sql file based on what you find.  
2. Next, let's build out video_games a bit more. Because our database is very sparse, adding new games is going to be a common action that we take. Let's simplify the INSERT INTO ... VALUES () process by creating a stored procedure that doesn't require us to remember the attribute names. Now we can focus even more on providing values for the database.
		Use CREATE PROCEDURELinks to an external site. to create an add_video_game stored procedure.
		Once the procedure is created, we can CALLLinks to an external site. it whenever we need to add new entries.
		Use the new stored procedure to add the following:
			1. Tony Hawk's Pro Skater 3, October 28, 2001, Playstation 2
			2. Tetris, June 14, 1989, Gameboy
			3. Mario Kart 64, December 14, 1996, Nintendo 64
			4. Crazy Taxi, January 24, 2000, Dreamcast
			5. NBA Street Vol. 2, April 29, 2003, Xbox
			6. Baldur's Gate, December 21, 1998, PC
			7. Heroes of Might and Magic III, February 28, 1999, PC
3. Repeat the process in step 2 for video game characters. 
		Use CREATE PROCEDURE to create an add_game_character stored procedure.
		Call the  add_game_character stored procedure to add the following:
			1. Tony Hawk, 6
			2. Biggie Little, 10
			3. Stretch, 10
			4. Edwin Odesseiron, 11
			5. Jaheira, 11
			6. Xzar, 11
4. Let's find out about relationships between the data stored in the three tables by creating the following JOIN statements:
		For all joins, please aliasLinks to an external site. your table names. This prevents you from having to type out schema.full_relation_name everytime you use an attribute to project, restrict, or join.
		An INNER JOIN between video_games and game_characters.
			Output: Show the video game name and the game character name.
			Logistics: Use game_id as the attribute on which both tables should join 
 		A LEFT JOIN of video_games on game_characters 
			Output: Show the video game name and the game character name. ORDER BYLinks to an external site. game name then character name.
			Logistics: Use game_id as the attribute to join the tables 
		A LEFT JOIN of video_games on tabletop_games 
			Output: Show the year of the release_date for each video game, the video game name, and the tabletop game that won the award in that year 
			Logistics
				Use award year and the year of release_ date as the attribute to join the tables
				The date_partLinks to an external site. function will be very helpful in extracting the year.
*/

ALTER TABLE games
    RENAME TO video_games;
	
--autoupdate of foreign key even when name changes

CREATE PROCEDURE public.add_video_game (g_name text, r_date date, g_system text) 
	LANGUAGE SQL
	AS $$
	INSERT INTO video_games (game_name, release_date, game_system)
	VALUES (g_name, r_date, g_system);
	$$;


CALL public.add_video_game('Tony Hawk''s Pro Skater 3', 'October 28, 2001', 'Playstation 2');
CALL public.add_video_game('Tetris', 'June 14, 1989', 'Gameboy');
CALL public.add_video_game('Mario Kart 64', 'December 14, 1996','Nintendo 64');
CALL public.add_video_game('Crazy Taxi', 'January 24, 2000', 'Dreamcast');
CALL public.add_video_game('NBA Street Vol. 2', 'April 29, 2003', 'Xbox');
CALL public.add_video_game('Baldur''s Gate', 'December 21, 1998', 'PC');
CALL public.add_video_game('Heroes of Might and Magic III', 'February 28, 1999', 'PC');


CREATE PROCEDURE public.add_game_character (c_name text, g_id int) 
	LANGUAGE SQL
	AS $$
	INSERT INTO game_characters (character_name, game_id)
	VALUES (c_name, g_id);
	$$;


CALL public.add_game_character('Tony Hawk', '6');
CALL public.add_game_character('Biggie Little', '10');
CALL public.add_game_character('Stretch', '10');
CALL public.add_game_character('Edwin Odesseiron', '11');
CALL public.add_game_character('Jaheira', '11');
CALL public.add_game_character('Xzar', '11');


SELECT vg.game_name, gc.character_name
	FROM public.video_games vg 
	INNER JOIN public.game_characters gc
	ON vg.game_id=gc.game_id;


SELECT vg.game_name, gc.character_name
	FROM public.video_games vg
	LEFT JOIN public.game_characters gc
	ON vg.game_id=gc.character_id
	ORDER BY 1,2;


SELECT vg.release_date, vg.game_name, tg.award_year, tg.game_name
	FROM public.video_games vg
	LEFT JOIN public.tabletop_games tg
	ON date_part('year', vg.release_date)=tg.award_year;
