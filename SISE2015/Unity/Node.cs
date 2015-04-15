using System.Collections.Generic;
using UnityEngine;

public class Node {
    #region Variables
    public Vector3 position;
    public List<Node> neighbors;
    #endregion

    #region Constructors
    public Node(Vector3 pos) {
        position = pos;
        neighbors = new List<Node>();
    }
    #endregion

    #region Methods
    public void AddNeighbor(Node neighbor) {
        neighbors.Add(neighbor);
    }

    public void VisualizeNode(float radius) {
        Gizmos.DrawSphere(position, radius);
    }

    public void VisualizeConnections() {
        foreach (Node n in neighbors) {
            Gizmos.DrawLine(position, n.position);
        }
    }
    #endregion
}
