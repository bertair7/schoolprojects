; Justin Foxhoven and Ryan Blair
; 0-8:   Result1
; 9-16:  Result2
; 17-24: Result3
; 25-30: Result4
		.ORIG 		x3300
;
Q1		.STRINGZ	"\nWhat is your favorite genre of music?\n	1 - Classical\n	2 - Dubstep\n	3 - Country\n	4 - Metal\n"
Q1Ans		.FILL		#5
		.FILL		#8
		.FILL		#2
		.FILL		#10
;
Q2		.STRINGZ	"\nWhat is your favorite sport?\n	1 - Swimming\n	2 - Lacrosse\n	3 - Basketball\n 4 - Football\n"
Q2Ans		.FILL		#8
		.FILL		#10
		.FILL		#2
		.FILL		#5
;
Q3		.STRINGZ	"\nWhat is your favorite MOBA?\n 	1 - What is a MOBA???\n	2 - Dota 2\n 3 - League of Legends\n	4 - SMITE IS LIFE GET GUD NOOOOOB\n"
Q3Ans		.FILL		#2
		.FILL		#10
		.FILL		#8
		.FILL		#5
;
;
Result1		.STRINGZ	"\nYou can come out of that cave now.\n"
Result2		.STRINGZ	"\nMaybe you should get out more.\n"
Result3		.STRINGZ	"\nWe need to hang out real soon.\n"
Result4		.STRINGZ	"\nOMG We have so much in common!\n"

		.END
