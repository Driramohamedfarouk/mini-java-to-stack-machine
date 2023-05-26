class Main {
    int x = 5 ;
    int z ;
    z = 2*x ;
    public int call(int x , int y){
        int y = 0 ;
        int x1 = 0 ;
        z = x1+y ;
    }

    public int start(){
        z=z*2 ;
    }

    if(x>5){
        z = x+5 ;
    }else{
        z = z - 5 ;
    }
    call(x,y,z);
    x = x+ 1 ;
    start();
}