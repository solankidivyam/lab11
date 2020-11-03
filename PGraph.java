import java.util.Arrays;

class PGraph {

    public void Prim(int G[][], int V) {

        int INF = 9999999;


        int no_edge;
        boolean[] selected = new boolean[V];

        Arrays.fill(selected, false);

        no_edge = 0;

        selected[0] = true;


        System.out.println("Edge : Weight");
        int sum = 0;
        while (no_edge < V - 1) {
            int min = INF;
            int x = 0; // row number
            int y = 0; // col number

            for (int i = 0; i < V; i++) {
                if (selected[i] == true) {
                    for (int j = 0; j < V; j++) {
                        // not in selected and there is an edge
                        if (!selected[j] && G[i][j] != 0) {
                            if (min > G[i][j]) {
                                min = G[i][j];
                                x = i;
                                y = j;
                            }
                        }
                    }
                }
            }
            sum = sum + G[x][y];
            System.out.println(x + " - " + y + " :  " + G[x][y]);
            System.out.println("The sum after this is " + sum);

            selected[y] = true;
            no_edge++;
        }
    }

    public static void main(String[] args) {
        PGraph g = new PGraph();

        // number of vertices in grapj
        int V = 5;

        // create a 2d array of size 5x5
        // for adjacency matrix to represent graph
        int[][] G = { { 0, 2, 0, 8, 5 },
                      { 2, 0, 1, 10, 9 },
                      { 0, 1, 0, 0, 13 },
                      { 8, 10, 0, 0, 5 },
                      { 5, 9, 13, 5, 0 } };

        g.Prim(G, V);
    }
}