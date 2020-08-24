#include <stdio.h>
#include "parser.h"
#include "front.h"

static void error();

/* expr
 * Parses strings in the language generated by the rule:
 * <expr> -> <rexpr> {(&& | ||) <rexpr>}
 */
void expr()
{
    printf("Enter <expr>\n");
    rexpr();
    while (nextToken == AND_OP || nextToken == OR_OP) {
        /* && case */
		if(nextToken == AND_OP){
          lex();
          if(nextToken != AND_OP){
            error();
            /*if nextToken is not & 
              process as error */
          }
          else{
            lex();
            rexpr();
          }
        }
        /* || case*/
        if(nextToken == OR_OP){
          lex();
          if(nextToken != OR_OP){
            error();
            /*if nextToken is not |
              process as error */
          }
          else{
            lex();
            rexpr();
          }
        }
    }
    printf("Exit <expr>\n");
}

/* rexpr
 * Parses strings in the language generated by the rule:
 * <rexpr> -> <aexpr> {(==|!=|<|>) <aexpr>}
 */
void rexpr()
{
    printf("Enter <rexpr>\n");
    aexpr();
    while (nextToken == EQUAL_OP || nextToken == NOT_OP || nextToken == LESS_OP || nextToken == MORE_OP) {
        /* == case */
        if((nextToken == EQUAL_OP)||(nextToken == NOT_OP)){
            if(nextToken == EQUAL_OP){
				lex();
            	if(nextToken == EQUAL_OP){
                	lex();
                	aexpr();
            	}
            	else{
            		/*if nextToken is not = , process as error */
                	error();
            	}
        	}
        	/* != case */
        	if(nextToken == NOT_OP){
            	lex();
            	if(nextToken == EQUAL_OP){
                  	lex();
                	aexpr();
            	}
            	else{
            		/*if nextToken is not =, process as error */
            	    error();
        	    }
      	  	}
      	}
        /* <,> case */
        else{
          lex();
          aexpr();
        }
    }
    printf("Exit <rexpr>\n");
}

/* aexpr
 * Parses strings in the language generated by the rule:
 * <expr> -> <term> {(+ | - ) <term>}<te
 */
void aexpr() 
{
    printf("Enter <aexpr>\n");

    /* Parse the first term */
    term();
    /* As long as the next token is + or -, get
    the next token and parse the next term */
    while (nextToken == ADD_OP || nextToken == SUB_OP) {
        lex();
        term();
    }
    printf("Exit <aexpr>\n");
} /* End of function expr */

/* term
 * Parses strings in the language generated by the rule:
 * <term> -> <factor> {(* | /) <factor>)
 */
void term() 
{
    printf("Enter <term>\n");
    /* Parse the first factor */
    factor();
    /* As long as the next token is * or /, get the
    next token and parse the next factor */
    while (nextToken == MULT_OP || nextToken == DIV_OP) {
            lex();
            factor();
    }
    printf("Exit <term>\n");
} /* End of function term */

/* factor
 * Parses strings in the language generated by the rule:
 * <factor> -> id | int_constant | ( <expr )
 * */
void factor() 
{
    printf("Enter <factor>\n");
    /* Determine which RHS */
    if (nextToken == IDENT || nextToken == INT_LIT) {
        lex(); /* Get the next token */
    } 
	else {
        /* If the RHS is (<expr>), call lex to pass over the 
        left parenthesis, call expr, and check for the right 
        parenthesis */
    	if((nextToken == LEFT_PAREN)||(nextToken == NOT_OP)){
			if(nextToken == LEFT_PAREN) {
            	lex(); 
            	expr();
            	if(nextToken == RIGHT_PAREN) {
                	lex(); 
            	} 
				else{ 
                	error();
            	}
        	}
         /* if the RHS is !<factor> call lex(!) and call <factor>*/
        	if(nextToken == NOT_OP){
        	    lex();
            	factor();
        	}
    	}
        /* End of if (nextToken == ... */
        /* It was not an id, an integer literal, or a left parenthesis */
        else{ 
            error(); 
        }
    } /* End of else */
    printf("Exit <factor>\n");;
} /* End of function factor */

static void error(){
    printf("Error (more is desired, but not implemented).\n");
}

