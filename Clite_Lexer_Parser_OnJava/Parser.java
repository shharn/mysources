import java.util.*;

public class Parser {
    // Recursive descent parser that inputs a C++Lite program and 
    // generates its abstract syntax.  Each method corresponds to
    // a concrete syntax grammar rule, which appears as a comment
    // at the beginning of the method.
  
    Token token;          // current token from the input stream
    Lexer lexer;
  
    public Parser(Lexer ts) { // Open the C++Lite source program
        lexer = ts;                          // as a token stream, and
        token = lexer.next();            // retrieve its first Token
    }
  
    private String match (TokenType t) {
        String value = token.value();
        if (token.type().equals(t))
            token = lexer.next();
        else
            error(t);
        return value;
    }
  
    private void error(TokenType tok) {
        System.err.println("Syntax error: expecting: " + tok 
                           + "; saw: " + token);
        System.exit(1);
    }
  
    private void error(String tok) {
        System.err.println("Syntax error: expecting: " + tok 
                           + "; saw: " + token);
        System.exit(1);
    }
  
    public Program program() {
        // Program --> int main ( ) '{' Declarations Statements '}'
        TokenType[ ] header = {TokenType.Int, TokenType.Main,
                          TokenType.LeftParen, TokenType.RightParen};
        for (int i=0; i<header.length; i++)   // bypass "int main ( )"
            match(header[i]);
        match(TokenType.LeftBrace);
        // student exercise
        Declarations ds = declarations();
        Block b = statements();
        return new Program(ds, b);  // student exercise
    }
  
    private Declarations declarations () {
        // Declarations --> { Declaration }
        Declarations decls = new Declarations();
        declaration(decls);
        return decls;  // student exercise
    }
  
    private void declaration (Declarations ds) {
        // Declaration  --> Type Identifier { , Identifier } ;
        // student exercise
        while(isType()){
	        Type t = type();
	        Variable v;			
	        token = lexer.next();
	        while(!token.type().equals(TokenType.Semicolon)){
		        v = new Variable(match(TokenType.Identifier));
				Declaration d = new Declaration(v, t);
				ds.add(d);
	        }
			match(TokenType.Semicolon);
        }
    }
  
    private Type type () {
        // Type  -->  int | bool | float | char 
        Type t = null;
        // student exercise
		if(token.type().equals(TokenType.Int))
			t = Type.INT;
		else if(token.type().equals(TokenType.Char))
			t = Type.CHAR;
		else if(token.type().equals(TokenType.Float))
			t = Type.FLOAT;
		else if(token.type().equals(TokenType.Bool))
			t = Type.BOOL;
		else
			t = Type.UNDEFINED;
        return t;          
    }
  
    private Statement statement() {
        // Statement --> ; | Block | Assignment | IfStatement | WhileStatement
        Statement s = null;
        // student exercise
		if(token.type().equals(TokenType.Identifier))
			s = assignment();
		else if(token.type().equals(TokenType.If))
			s = ifStatement();
		else if(token.type().equals(TokenType.While))
			s = whileStatement();
		else if(token.type().equals(TokenType.LeftBrace))
			s = statements();
		else if(token.type().equals(TokenType.Semicolon)){
			token = lexer.next();
			s = new Skip();
		}else
			error("Block | Assignment | IfStatement | WhileStatement");
        return s;
    }
  
    private Block statements () {
        // Block --> '{' Statements '}'
        Block b = new Block();
		Statement s = null;
        // student exercise
		while(token.type().equals(TokenType.RightBrace) == false){
			s = statement();
			b.members.add(s);
		}
        return b;
    }
  
    private Assignment assignment () {
        // Assignment --> Identifier = Expression ;
		Variable t = (Variable)expression();
		match(TokenType.Assign);
		Expression source = expression();
        return new Assignment(t, source);  // student exercise
    }
  
    private Conditional ifStatement () {
        // IfStatement --> if ( Expression ) Statement [ else Statement ]
		match(TokenType.If);
		match(TokenType.LeftParen);
		Expression test = expression();
		match(TokenType.RightParen);

		Statement then = null;
		if(token.type().equals(TokenType.LeftBrace)){
			then = statements();
			match(TokenType.RightBrace);
		} else 
			then = statement();

		Statement elseStatement = new Skip();
		if(token.type().equals(TokenType.Else)){
			if(token.type().equals(TokenType.LeftBrace)){
				elseStatement = statements();
				match(TokenType.RightBrace);
			} else 
				elseStatement = statement();
		}
        return new Conditional(test, then, elseStatement);  // student exercise
    }
  
    private Loop whileStatement () {
        // WhileStatement --> while ( Expression ) Statement
		token = lexer.next();
		match(TokenType.LeftParen);
		Expression test = expression();
		match(TokenType.RightParen);
		Statement body = null;
		if(token.type().equals(TokenType.LeftBrace)){
			match(TokenType.LeftBrace);
			body = statements();
			match(TokenType.RightBrace);
		}
		else
			body = statement();
        return new Loop(test, body);  // student exercise
    }

    private Expression expression () {
        // Expression --> Conjunction { || Conjunction }
		Expression e = conjunction();
		if(token.type().equals(TokenType.Or)){
			Operator op = new Operator(match(token.type()));
			Expression conjunction2 = conjunction();
			e = new Binary(op, e, conjunction2);
		}
        return e;  // student exercise
    }
  
    private Expression conjunction () {
        // Conjunction --> Equality { && Equality }
		Expression e = equality();
		if(token.type().equals(TokenType.And)){
			Operator op = new Operator(match(token.type()));
			Expression equ2 = equality();
			e = new Binary(op, e, equ2);
		}
        return e;  // student exercise
    }
  
    private Expression equality () {
        // Equality --> Relation [ EquOp Relation ]
		Expression e = relation();
		if(isEqualityOp()){
			Operator op = new Operator(match(token.type()));
			Expression rel2 = relation();
			e = new Binary(op, e, rel2);
		}
        return e;  // student exercise
    }

    private Expression relation (){
        // Relation --> Addition [RelOp Addition] 
		Expression e = addition();
		if(isRelationalOp()){
			Operator op = new Operator(match(token.type()));
			Expression add2 = relation();
			e = new Binary(op, e, add2);
		}	
        return e;  // student exercise
    }
  
    private Expression addition () {
        // Addition --> Term { AddOp Term }
        Expression e = term();
        while (isAddOp()) {
            Operator op = new Operator(match(token.type()));
            Expression term2 = term();
            e = new Binary(op, e, term2);
        }
        return e;
    }
  
    private Expression term () {
        // Term --> Factor { MultiplyOp Factor }
        Expression e = factor();
        while (isMultiplyOp()) {
            Operator op = new Operator(match(token.type()));
            Expression term2 = factor();
            e = new Binary(op, e, term2);
        }
        return e;
    }
  
    private Expression factor() {
        // Factor --> [ UnaryOp ] Primary 
        if (isUnaryOp()) {
            Operator op = new Operator(match(token.type()));
            Expression term = primary();
            return new Unary(op, term);
        }
        else return primary();
    }
  
    private Expression primary () {
        // Primary --> Identifier | Literal | ( Expression )
        //             | Type ( Expression )
        Expression e = null;
        if (token.type().equals(TokenType.Identifier)) {
            e = new Variable(match(token.type()));
        } else if (isLiteral()) {
            e = literal();
        } else if(isBooleanLiteral()){
        	e = new BoolValue(Boolean.parseBoolean(match(token.type())));
        } else if (token.type().equals(TokenType.LeftParen)) {
            token = lexer.next();
            e = expression();       
            match(TokenType.RightParen);
        } else if (isType( )) {
            Operator op = new Operator(match(token.type()));
            match(TokenType.LeftParen);
            Expression term = expression();
            match(TokenType.RightParen);
            e = new Unary(op, term);
        } else error("Identifier | Literal | ( | Type");
        return e;
    }

    private Value literal() {
    	Value v = null;
		if(token.type().equals(TokenType.IntLiteral))
			v = new IntValue(Integer.parseInt(match(token.type())));
		else if(token.type().equals(TokenType.CharLiteral))
			v = new CharValue(match(token.type()).charAt(0));
		else if(token.type().equals(TokenType.FloatLiteral))
			v = new FloatValue(Float.parseFloat(match(token.type())));
		return v;
        // student exercise
    }
  

    private boolean isAddOp( ) {
        return token.type().equals(TokenType.Plus) ||
               token.type().equals(TokenType.Minus);
    }
    
    private boolean isMultiplyOp( ) {
        return token.type().equals(TokenType.Multiply) ||
               token.type().equals(TokenType.Divide);
    }
    
    private boolean isUnaryOp( ) {
        return token.type().equals(TokenType.Not) ||
               token.type().equals(TokenType.Minus);
    }
    
    private boolean isEqualityOp( ) {
        return token.type().equals(TokenType.Equals) ||
            token.type().equals(TokenType.NotEqual);
    }
    
    private boolean isRelationalOp( ) {
        return token.type().equals(TokenType.Less) ||
               token.type().equals(TokenType.LessEqual) || 
               token.type().equals(TokenType.Greater) ||
               token.type().equals(TokenType.GreaterEqual);
    }
    
    private boolean isType( ) {
        return token.type().equals(TokenType.Int)
            || token.type().equals(TokenType.Bool) 
            || token.type().equals(TokenType.Float)
            || token.type().equals(TokenType.Char);
    }
    
    private boolean isLiteral( ) {
        return token.type().equals(TokenType.IntLiteral) ||
            token.type().equals(TokenType.FloatLiteral) ||
            token.type().equals(TokenType.CharLiteral);
    }
    
    private boolean isBooleanLiteral( ) {
        return token.type().equals(TokenType.True) ||
            token.type().equals(TokenType.False);
    }
    
    /*
    public static void main(String args[]) {
        Parser parser  = new Parser(new Lexer("C:\\Users\\Dream\\흔적들\\프로그래밍 언어론\\softwarestudents\\softwarestudents\\ch02-08 (Clite)\\programs\\nested.cpp"));
        Program prog = parser.program();
        prog.display();           // display abstract syntax tree
    } //main
	*/
} // Parser
