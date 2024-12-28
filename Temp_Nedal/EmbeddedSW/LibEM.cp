#line 1 "C:/Users/Lenovo/Desktop/4thyear_sim1/EmbeddedSW/LibEM.c"
#line 66 "C:/Users/Lenovo/Desktop/4thyear_sim1/EmbeddedSW/LibEM.c"
void interrupt(void)
{

}

void main()
{
  PORTA |= (1<<1) ;
  PORTA &= ~ (1<<0) ;
  ~( PORTA & (1<<0) ) ;
  PORTA & (1<<0) ;

}
