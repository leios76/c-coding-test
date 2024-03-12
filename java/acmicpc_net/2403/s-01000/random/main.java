import java.util.Random;

class Main {
   public static int max_n = 10;
   public static int min_n = 1;
   public static int max_v = 10;
   public static int min_v = 1;

   public static void main(String[] args) {

      Random rand = new Random();

      int n = rand.nextInt(max_n - min_n + 1) + min_n;
      System.out.println(n);
      for (int i = 0; i < n; i++) {
         int v = rand.nextInt(max_v - min_v + 1) + min_v;
         System.out.println(v);
      }
   }
}