using System.Collections.Generic;
using UnityEngine;

public class SISEGraphGenerator : MonoBehaviour {
    #region Variables
    public List<Node> nodes = new List<Node>();

    private int depth = 2;
    private int players = 6;
    private float distance = 2f;
    #endregion

    #region Monobehaviour Methods
    void Start () {
        GenerateNodes();
    }

    void OnDrawGizmos() {
        Gizmos.color = new Color(1f, 0f, 0f, 0.8f);

        foreach (Node node in nodes) {
            node.VisualizeNode(0.5f);
            node.VisualizeConnections();
        }
    }
    #endregion

    #region Methods
    private void GenerateNodes() {
        // initial node
        nodes.Add(new Node(Vector3.zero));

        // ring-shaped nodes
        float currDistance = distance;
        float angle = 360f / players;

        GameObject temp = new GameObject();
        Transform t = temp.transform;           // cannot create a new Transform();

        for (int i = 0; i < depth; i++) {
            t.position = new Vector3(0, currDistance);
            // spawn nodes
            for (int j = 0; j < players; j++) {
                t.RotateAround(Vector3.zero, Vector3.forward, angle);
                nodes.Add(new Node(t.position));
            }

            // create connections
            for (int j = 1; j <= players; j++) {
                int index = nodes.Count - j;
                Node n = nodes[index];

                // connect to higher indexed node OR bridge the gap between first and last node
                n.AddNeighbor(j != 1 ? nodes[index + 1] : nodes[index - players + 1]);

                // connect to lower indexed node OR bridge the gap between first and last node
                n.AddNeighbor(j != players ? nodes[index - 1] : nodes[index + players - 1]);

                // connect to a lower ring node OR to the central node (in the case of the first ring)
                index -= players;
                n.AddNeighbor(index > 0 ? nodes[index] : nodes[0]);
            }

            currDistance += distance;
        }
    }
    #endregion
}
