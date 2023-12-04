import java.util.*;

public class modExpo {
    public static int k = 0;
    public static int modularExp(int b, int[] bi, int m){
        int res = 1;
        int power = b % m;
        for(int i=0; i < bi.length; i++){
            if(bi[i]==1)
                res = (res*power) % m;
            power = (power*power) % m;
        }
        return res;
    }
    public static int[] intToBin(int x){
        int num = x;
        int size = 10;
        int[] binary;
        binary = new int[size];
        int[] temp = new int[size];

        while(num != 0){
            temp[k] = num % 2;
            num = num / 2;
            k++;
        }

        return temp;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter base number : ");
        int base = sc.nextInt();
        System.out.println("Enter exponent number : ");
        int expo = sc.nextInt();
        System.out.println("Enter modulus number : ");
        int mod = sc.nextInt();
        int[] bin ;
        bin = intToBin(expo);
        System.out.print("Binary of " + expo + " = ");
        for(int i =k; i >= 0; i--){
            System.out.print(bin[i]);
        }
        System.out.println();
        int res = modularExp(base,bin,mod);
        System.out.println("Result : " + base + "^" + expo + " % " + mod + " = " + res);
    }
}
