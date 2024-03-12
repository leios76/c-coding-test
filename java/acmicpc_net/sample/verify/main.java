import java.util.Scanner;

class Main {
   private static int N;
   private static int[] V;

   public static void solve() {
      int result = 0;
      for (int n = 0; n < N; n++) {
         System.out.println(V[n]);
      }
      System.out.printf("%d\n", result);
   }

   public static void initData() {
      Scanner sc = new Scanner(System.in);
      N = sc.nextInt();
      V = new int[N];
      for (int n = 0; n < N; n++) {
         V[n] = sc.nextInt();
      }
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