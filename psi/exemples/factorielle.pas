(* Exemple 1: Calcule de la factorielle
 * Note		: Pour quitter le programme taper 0
 *)
program factorielle;
const
	max = 13;
var
	res, n;

procedure fact();
var
	i, s;
begin
	(* Calculer de la factorielle *)
	i := 1;
	s := 1;
	while i <= n do
	begin
		s := s * i;
		i := i + 1;
	end;
	res := s;
end;

begin
	n := 1;
	(* Taper 0 pour quitter *)
	while n<>0 do
	begin
		(* Entrer un nombre inferieur a max *)
		read(n);
		while n > max do
			read(n);

		fact();
		write(res);
	end;
end.
