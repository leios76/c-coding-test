import java.util.Scanner;

class Main {
   private static int a;
   private static int b;

   public static void solve() {
      System.out.printf("%d\n", a + b);
   }

   public static void initData() {
      Scanner sc = new Scanner(System.in);
      a = sc.nextInt();
      b = sc.nextInt();
      sc.close();
   }

   public static void main(String[] args) {
      int t = 1;

      //Scanner sc = new Scanner(System.in);
      //t = sc.nextInt();
      //sc.close();

      for (int i = 0; i < t; i++) {
         initData();
         solve();
      }
   }
}