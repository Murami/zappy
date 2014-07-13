all:
	make -C server all
	make -C graphic_client all
	cp ia/encore.py .
	cp server/server_zappy .
	cp graphic_client/zappy-graphic .

clean:
	make -C server clean
	make -C graphic_client clean

fclean:
	make -C server fclean
	make -C graphic_client fclean
	rm encore.py
	rm server_zappy
	rm zappy-graphic

re:
	make -C server re
	make -C graphic_client re
	cp ia/encore.py .
	cp server/server_zappy .
	cp graphic_client/zappy-graphic .

.PHONY:	all clean fclean re
