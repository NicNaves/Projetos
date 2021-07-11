:- module(login, 
		  [
			  %Predicados para o Front-End
			  login/2,

			  %Predicados para o Back-End
			  login_validate/2
		  ]).

/**********************************************************************************/
/****************************** BACK-END ******************************************/
/**********************************************************************************/

login_validate(post, Pedido):-
	catch(http_parameters(Pedido, [
		login(Login, [string]),
		password(Senha, [string])
	]), _E, fail), 
	usuario:usuario(_, _, _, Login, Senha, _),
	http_redirect(moved, location_by_id(home), []).

login_validate(post, _Pedido):-
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/login/loginfail.html', LoginPageFail, []),
	reply_html_page(Head, LoginPageFail).

/**********************************************************************************/
/****************************** FRONT-END *****************************************/
/**********************************************************************************/

login(get, _Pedido):-
	load_html('./static/fixed/head.html', Head, []),
	load_html('./static/login/login.html', LoginPage, []),
	reply_html_page(Head, LoginPage).