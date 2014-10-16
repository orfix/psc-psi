(* Exemple 2: Calcule récursif de la factorielle
 * Note		: Pour quitter le programme taper 0
 *)
program factorielle2;
const
	max = 13;
var
	res, n;

procedure fact();
var
	i, s;
begin
	(* Calculer récursif de la factorielle *)
	if n>1 then
	begin
		res := res * n;
		n := n - 1;
		fact();
	end;
end;

begin
	n 	:= 1;
	(* Taper 0 pour quitter *)
	while n<>0 do
	begin
		(* Entrer un nombre inferieur a max *)
		read(n);
		while n > max do
			read(n);

		res := 1;
		fact();
		write(res);
	end;
end.
