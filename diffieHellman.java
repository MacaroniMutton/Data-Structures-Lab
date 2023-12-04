import java.util.*;
import java.lang.Math;
public class diffieHellman {
    // g^A mod n
    public static int power(long g, int a, long n){
        return (((int)Math.pow(g,a))%(int)n);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        long n; //modulus n
        long g; //base g
        //Alice and bob deciding large prime number publicly
        System.out.println("Enter a prime number for g : ");
        g = sc.nextInt();
        System.out.println("Enter a prime number for n : ");
        n = sc.nextInt();

        //Alice and bob choosing their private key(number) restricted to themselves
        int max = 100;
        int min = 1;
        int range = max - min + 1;
        int A = (int)(Math.random()*range) + min;
        System.out.println("Alice's private number = " + A);
        int B = (int)(Math.random()*range) + min;
        System.out.println("Bob's private number = " + B);
        System.out.println();
        //calculating x -> Alice and y -> Bob
        int x = power(g,A,n);
        int y = power(g,B,n);


        //Alice shares her calculated x with bob,
        // bob shares his calculated y with alice, and they calculate their keys
        int keyA = power(y,A,n);
        int keyB = power(x,B,n);

        System.out.println("Key alice calculated : " + keyA);
        System.out.println("Key bob calculated : " + keyB);

        // x = g^A % n    y = g^B % n
        // k1 = y^A % n = (g^B % n)^A % n = g^B^A % n = g ^ BA % n
        // k2 = x^B % n = (g^A % n)^B % n = g^A^B % n = g ^ AB % n

    }
}


