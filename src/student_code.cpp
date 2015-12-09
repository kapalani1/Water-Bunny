/*
 * Student solution for CMU 15-462 Project 2 (MeshEdit)
 *
 * Implemented by Karthic Palaniappan 
 * & Reference Implementation on 12/2/15.
 *
 */

#include "student_code.h"
#include "mutablePriorityQueue.h"
#include "Eigen/Sparse"

namespace CMU462
{
    VertexIter HalfedgeMesh::splitEdge( EdgeIter e0 )
    {
        // first handle boundary case
        if( e0->isBoundary() )
        {
            // get current elements
            HalfedgeIter h5 = e0->halfedge(); if( h5->isBoundary() ) h5 = h5->twin();
            HalfedgeIter h4 = h5->next();
            HalfedgeIter h1 = h4->next();
            HalfedgeIter hb = h5->twin();
            VertexIter v1 = h1->vertex();
            VertexIter v3 = h5->vertex();
            VertexIter v4 = h4->vertex();
            EdgeIter e1 = h1->edge();
            EdgeIter e4 = h4->edge();
            FaceIter f1 = h1->face();
            FaceIter fb = hb->face();
            
            // get previous and next half edge along the boundary loop
            HalfedgeIter hbp = hb;
            do
            {
                hbp = hbp->twin()->next();
            }
            while( hbp->twin()->next() != hb );
            hbp = hbp->twin();
            HalfedgeIter hbn = hb->next();
            
            // allocate new elements
            VertexIter v5 = newVertex();
            EdgeIter e5 = newEdge();
            EdgeIter e7 = newEdge();
            EdgeIter e8 = newEdge();
            FaceIter f3 = newFace();
            FaceIter f6 = newFace();
            HalfedgeIter h8  = newHalfedge();
            HalfedgeIter h9  = newHalfedge();
            HalfedgeIter h11 = newHalfedge();
            HalfedgeIter h13 = newHalfedge();
            HalfedgeIter hb1 = newHalfedge();
            HalfedgeIter hb2 = newHalfedge();
            
            // set new vertex location
            v5->position = ( v3->position + v4->position ) / 2.;
            
            // connect new elements
            h1->setNeighbors( h11, h1->twin(), v1, e1, f3 );
            h4->setNeighbors( h9,  h4->twin(), v4, e4, f6 );
            h8->setNeighbors( h4,  hb1,      v5, e8, f6 );
            h9->setNeighbors( h8,  h13,      v1, e5, f6 );
            h11->setNeighbors( h13, hb2,     v3, e7, f3 );
            h13->setNeighbors( h1,  h9,      v5, e5, f3 );
            hb1->setNeighbors( hb2, h8,  v4, e8, fb );
            hb2->setNeighbors( hbn, h11, v5, e7, fb );
            hbp->next() = hb1;
            v1->halfedge() = h1;
            v3->halfedge() = h11;
            v4->halfedge() = h4;
            v5->halfedge() = h13;
            e1->halfedge() = h1;
            e4->halfedge() = h4;
            e5->halfedge() = h9;
            e7->halfedge() = h11;
            e8->halfedge() = h8;
            f3->halfedge() = h1;
            f6->halfedge() = h4;
            fb->halfedge() = hb1;
            
            // deallocate old elements
            deleteEdge( e0 );
            deleteFace( f1 );
            deleteHalfedge( h5 );
            deleteHalfedge( hb );
            
            return v5;
        }
        else
        {
            // get current elements
            HalfedgeIter h5 = e0->halfedge();
            HalfedgeIter h6 = h5->twin();
            HalfedgeIter h4 = h5->next();
            HalfedgeIter h1 = h4->next();
            HalfedgeIter h3 = h6->next();
            HalfedgeIter h2 = h3->next();
            VertexIter v1 = h1->vertex();
            VertexIter v2 = h2->vertex();
            VertexIter v3 = h3->vertex();
            VertexIter v4 = h4->vertex();
            EdgeIter e1 = h1->edge();
            EdgeIter e2 = h2->edge();
            EdgeIter e3 = h3->edge();
            EdgeIter e4 = h4->edge();
            FaceIter f1 = h1->face();
            FaceIter f2 = h2->face();
            
            // allocate new elements
            VertexIter v5 = newVertex();
            EdgeIter e5 = newEdge();
            EdgeIter e6 = newEdge();
            EdgeIter e7 = newEdge();
            EdgeIter e8 = newEdge();
            FaceIter f3 = newFace();
            FaceIter f4 = newFace();
            FaceIter f5 = newFace();
            FaceIter f6 = newFace();
            HalfedgeIter h7  = newHalfedge();
            HalfedgeIter h8  = newHalfedge();
            HalfedgeIter h9  = newHalfedge();
            HalfedgeIter h10 = newHalfedge();
            HalfedgeIter h11 = newHalfedge();
            HalfedgeIter h12 = newHalfedge();
            HalfedgeIter h13 = newHalfedge();
            HalfedgeIter h14 = newHalfedge();
            
            // set new vertex location
            v5->position = ( v3->position + v4->position ) / 2.;
            
            // connect new elements
            h1->setNeighbors( h11, h1->twin(), v1, e1, f3 );
            h2->setNeighbors( h12, h2->twin(), v2, e2, f4 );
            h3->setNeighbors( h10, h3->twin(), v3, e3, f5 );
            h4->setNeighbors( h9,  h4->twin(), v4, e4, f6 );
            h7->setNeighbors( h3,  h11,      v5, e7, f5 );
            h8->setNeighbors( h4,  h12,      v5, e8, f6 );
            h9->setNeighbors( h8,  h13,      v1, e5, f6 );
            h10->setNeighbors( h7,  h14,      v2, e6, f5 );
            h11->setNeighbors( h13, h7,       v3, e7, f3 );
            h12->setNeighbors( h14, h8,       v4, e8, f4 );
            h13->setNeighbors( h1,  h9,       v5, e5, f3 );
            h14->setNeighbors( h2,  h10,      v5, e6, f4 );
            v1->halfedge() = h1;
            v2->halfedge() = h2;
            v3->halfedge() = h3;
            v4->halfedge() = h4;
            v5->halfedge() = h7;
            e1->halfedge() = h1;
            e2->halfedge() = h2;
            e3->halfedge() = h3;
            e4->halfedge() = h4;
            e5->halfedge() = h9;
            e6->halfedge() = h10;
            e7->halfedge() = h11;
            e8->halfedge() = h12;
            f3->halfedge() = h1;
            f4->halfedge() = h2;
            f5->halfedge() = h3;
            f6->halfedge() = h4;
            
            // deallocate old elements
            deleteEdge( e0 );
            deleteFace( f1 );
            deleteFace( f2 );
            deleteHalfedge( h5 );
            deleteHalfedge( h6 );
            
            return v5;
        }
    }
    
    VertexIter HalfedgeMesh::collapseEdge( EdgeIter e )
    {
        HalfedgeIter he; // dummy iterator
        
        // handle boundary case first
        if( e->isBoundary() )
        {
            // get pointers to the original geometry
            HalfedgeIter h0 = e->halfedge(); if( h0->isBoundary() ) h0 = h0->twin();
            HalfedgeIter h1 = h0->next();
            HalfedgeIter h2 = h1->next();
            HalfedgeIter h1f = h1->twin();
            HalfedgeIter h2f = h2->twin();
            HalfedgeIter hb = h0->twin();
            HalfedgeIter hbn = hb->next();
            HalfedgeIter hbp = hb; do { hbp = hbp->twin()->next(); } while( hbp->twin()->next() != hb ); hbp = hbp->twin();
            VertexIter v0 = h2->vertex();
            VertexIter v1 = h0->vertex();
            VertexIter v2 = h1->vertex();
            EdgeIter e1 = h1->edge();
            EdgeIter e2 = h2->edge();
            FaceIter f = h0->face();
            FaceIter fb = hb->face();
            
            // create new mesh elements
            VertexIter v = newVertex();
            EdgeIter e0 = newEdge();
            
            // link together elements
            // vertices
            v0->halfedge() = h1f;
            v->halfedge() = hbn;
            v->position = ( v1->position + v2->position ) / 2.;
            
            // edges
            e0->halfedge() = h1f;
            // faces
            fb->halfedge() = hbn;
            // halfedges
            he = v1->halfedge(); do { he->vertex() = v; he = he->twin()->next(); } while( he != v1->halfedge() );
            he = v2->halfedge(); do { he->vertex() = v; he = he->twin()->next(); } while( he != v2->halfedge() );
            h1f->twin() = h2f;
            h2f->twin() = h1f;
            h1f->edge() = h2f->edge() = e0;
            hbp->next() = hbn;
            
            // remove old elements
            deleteVertex( v1 );
            deleteVertex( v2 );
            deleteEdge( e );
            deleteEdge( e1 );
            deleteEdge( e2 );
            deleteFace( f );
            deleteHalfedge( h0 );
            deleteHalfedge( h1 );
            deleteHalfedge( h2 );
            deleteHalfedge( hb );
            
            return v;
        }
        else
        {
            // get fixed pointers to the original geometry
            HalfedgeIter h0 = e->halfedge();
            HalfedgeIter h1 = h0->twin();
            HalfedgeIter h00 = h0->next(), h01 = h00->next();
            HalfedgeIter h10 = h1->next(), h11 = h10->next();
            HalfedgeIter h00f = h00->twin();
            HalfedgeIter h01f = h01->twin();
            HalfedgeIter h10f = h10->twin();
            HalfedgeIter h11f = h11->twin();
            VertexIter v0 = h0->vertex();
            VertexIter v1 = h1->vertex();
            VertexIter v01 = h01->vertex();
            VertexIter v11 = h11->vertex();
            EdgeIter e00 = h00->edge();
            EdgeIter e01 = h01->edge();
            EdgeIter e10 = h10->edge();
            EdgeIter e11 = h11->edge();
            FaceIter f0 = h0->face();
            FaceIter f1 = h1->face();
            bool v0b = v0->isBoundary();
            bool v1b = v1->isBoundary();
            
            // check that the intersection of the 1-ring neighborhoods of the two
            // edge endpoints contains only the two vertices opposite the edge
            set<VertexCIter> neighbors;
            size_t n = 0;
            he = v0->halfedge(); do { n++; neighbors.insert( he->twin()->vertex() ); he = he->twin()->next(); } while( he != v0->halfedge() );
            he = v1->halfedge(); do { n++; neighbors.insert( he->twin()->vertex() ); he = he->twin()->next(); } while( he != v1->halfedge() );
            if( n - neighbors.size() != 2 )
            {
                return v0;
            }
            
            // create new mesh elements
            EdgeIter e0 = newEdge();
            EdgeIter e1 = newEdge();
            VertexIter v = newVertex();
            
            // link old elements to new ones
            // vertices
            v->halfedge() = h01f;
            // edges
            e0->halfedge() = h01f;
            e1->halfedge() = h11f;
            // faces
            // (nothing to do)
            // halfedges
            he = v0->halfedge(); do { he->vertex() = v; he = he->twin()->next(); } while( he != v0->halfedge() );
            he = v1->halfedge(); do { he->vertex() = v; he = he->twin()->next(); } while( he != v1->halfedge() );
            v01->halfedge() = h00f;
            v11->halfedge() = h10f;
            h00f->edge() = e0;
            h01f->edge() = e0;
            h10f->edge() = e1;
            h11f->edge() = e1;
            h00f->twin() = h01f;
            h01f->twin() = h00f;
            h10f->twin() = h11f;
            h11f->twin() = h10f;
            
            // if both vertices were on the bounday, put new vertex
            // at average of neighbors; otherwise, put it at the boundary
            if( v0b )
            {
                v->position = v0->position;
            }
            else if( v1b )
            {
                v->position = v1->position;
            }
            else
            {
                v->position = (v0->position+v1->position)/2.;
            }
            
            // remove old mesh elements
            deleteVertex( v0 );
            deleteVertex( v1 );
            deleteEdge( e );
            deleteEdge( e00 );
            deleteEdge( e01 );
            deleteEdge( e10 );
            deleteEdge( e11 );
            deleteFace( f0 );
            deleteFace( f1 );
            deleteHalfedge( h0 );
            deleteHalfedge( h00 );
            deleteHalfedge( h01 );
            deleteHalfedge( h1 );
            deleteHalfedge( h10 );
            deleteHalfedge( h11 );
            
            return v;
        }
    }
    
    EdgeIter HalfedgeMesh::flipEdge( EdgeIter e0 )
    {
        // skip boundary edges
        if( e0->isBoundary() ) return e0;
        
        // get current elements
        HalfedgeIter h1 = e0->halfedge();
        HalfedgeIter h2 = h1->next();
        HalfedgeIter h3 = h2->next();
        HalfedgeIter h4 = h1->twin();
        HalfedgeIter h5 = h4->next();
        HalfedgeIter h6 = h5->next();
        VertexIter v0 = h4->vertex();
        VertexIter v1 = h1->vertex();
        VertexIter v2 = h3->vertex();
        VertexIter v3 = h6->vertex();
        FaceIter f0 = h1->face();
        FaceIter f1 = h4->face();
        
        // recconnect current elements
        h1->setNeighbors( h6, h4, v2, e0, f0 );
        h2->setNeighbors( h1, h2->twin(), v0, h2->edge(), f0 );
        h3->setNeighbors( h5, h3->twin(), v2, h3->edge(), f1 );
        h4->setNeighbors( h3, h1, v3, e0, f1 );
        h5->setNeighbors( h4, h5->twin(), v1, h5->edge(), f1 );
        h6->setNeighbors( h2, h6->twin(), v3, h6->edge(), f0 );
        v0->halfedge() = h2;
        v1->halfedge() = h5;
        v2->halfedge() = h1;
        v3->halfedge() = h4;
        e0->halfedge() = h1;
        f0->halfedge() = h1;
        f1->halfedge() = h4;
        
        return e0;
    }
    
    void MeshResampler::upsample( HalfedgeMesh& mesh )
    // This routine should increase the number of triangles in the mesh using Loop subdivision.
    {
        // Each vertex and edge of the original surface can be associated with a vertex in the new (subdivided) surface.
        // Therefore, our strategy for computing the subdivided vertex locations is to *first* compute the new positions
        // using the connectity of the original (coarse) mesh; navigating this mesh will be much easier than navigating
        // the new subdivided (fine) mesh, which has more elements to traverse.  We will then assign vertex positions in
        // the new mesh based on the values we computed for the original mesh.
        
        // Compute updated positions for all the vertices in the original mesh, using the Loop subdivision rule.
        for( VertexIter v = mesh.verticesBegin(); v != mesh.verticesEnd(); v++ )
        {
            // We also want to mark this vertex as being a vertex of the original mesh.
            v->isNew = false;
            
            // Compute the Loop subdivision coefficient beta for this vertex.
            double n = (double) v->degree();
            double beta = ( n>3.? (3./(8.*n)) : 3./16. );
            
            // Iterate over neighbors of this vertex, accumulating the new position.
            HalfedgeIter h = v->halfedge();
            Vector3D p = (1.-n*beta) * v->position; // Add contribution of center vertex.
            do
            {
                p += beta * h->next()->vertex()->position; // Add contribution of neighbor vertex.
                
                h = h->twin()->next(); // Advance to the next neighbor.
            }
            while( h != v->halfedge() ); // End iteration over vertex neighbors.
            
            // Store the updated vertex position for this vertex.
            v->newPosition = p;
        }
        
        // Next, compute the updated vertex positions associated with edges.
        for( EdgeIter e = mesh.edgesBegin(); e != mesh.edgesEnd(); e++ )
        {
            // Grab the four vertex positions in the immediate neighborhood of this edge.
            Vector3D a0 = e->halfedge()->vertex()->position;
            Vector3D a1 = e->halfedge()->twin()->vertex()->position;
            Vector3D b0 = e->halfedge()->next()->next()->vertex()->position;
            Vector3D b1 = e->halfedge()->twin()->next()->next()->vertex()->position;
            
            // Compute the vertex position that will be associated with this edge's midpoint,
            // using the Loop subdivision weights.
            e->newPosition = (3./8.)*( a0 + a1 ) + (1./8.)*( b0 + b1 );
        }
        
        // Next, we're going to split every edge in the mesh, in any order.  For future
        // reference, we're also going to store some information about which subdivided
        // edges come from splitting an edge in the original mesh, and which edges are new.
        // In this loop, we only want to iterate over edges of the original mesh---otherwise,
        // we'll end up splitting edges that we just split (and the loop will never end!)
        int nEdges = mesh.nEdges();
        EdgeIter e = mesh.edgesBegin();
        for( int i = 0; i < nEdges; i++ ) // Loop over original mesh edges.
        {
            // Since the edge split will invalidate the current edge,
            // we need to grab a pointer to the next edge in the list NOW.
            EdgeIter nextEdge = e; nextEdge++;
            
            // Split the edge, and get a pointer to the newly inserted midpoint
            // vertex.  Note that HalfedgeMesh::splitEdge() should set the
            // halfedge pointer of this newly inserted vertex such that it points
            // to one of the edges in the original mesh.
            VertexIter m = mesh.splitEdge( e );
            
            // Mark this vertex as being new (i.e., not part of the original mesh).
            m->isNew = true;
            
            // Copy the position we computed for this edge to the new edge midpoint.
            m->newPosition = e->newPosition;
            
            // Flag the four edges incident on this vertex as either being old
            // (part of the original mesh) or new (a new edge coming from the split).
            bool isNew = false;
            HalfedgeIter h = m->halfedge();
            do
            {
                h->edge()->isNew = isNew;
                h = h->twin()->next();
                isNew = !isNew;
            }
            while( h != m->halfedge() );
            
            // Advance to the next edge, using the pointer we stored before.
            e = nextEdge;
        }
        
        // Finally, flip any new edge that connects an old and new vertex.
        for( EdgeIter e = mesh.edgesBegin(); e != mesh.edgesEnd(); e++ )
        {
            if( e->isNew )
            {
                // Get the endpoints of this edge.
                VertexIter v0 = e->halfedge()->vertex();
                VertexIter v1 = e->halfedge()->twin()->vertex();
                
                // If exactly one endpoint is new, flip this edge.
                if( ( v0->isNew && !v1->isNew ) ||
                   ( v1->isNew && !v0->isNew ) )
                {
                    mesh.flipEdge( e );
                }
            }
        }
        
        // Copy the updated vertex positions to the subdivided mesh.
        for( VertexIter v = mesh.verticesBegin(); v != mesh.verticesEnd(); v++ )
        {
            v->position = v->newPosition;
        }
        mesh.initializeVertices();
    }
    
    // Given an edge, the constructor for EdgeRecord finds the
    // optimal point associated with the edge's current quadric,
    // and assigns this edge a score based on how much quadric
    // error is observed at this optimal point.
    EdgeRecord::EdgeRecord( EdgeIter& _edge )
    : edge( _edge )
    {
        // Get pointers to the edge endpoints.
        VertexIter v0 = edge->halfedge()->vertex();
        VertexIter v1 = edge->halfedge()->twin()->vertex();
        
        // Compute the combined quadric from the endpoints.
        Matrix4x4 K0 = v0->quadric;
        Matrix4x4 K1 = v1->quadric;
        Matrix4x4 K = K0 + K1;
        
        // Build the 3x3 linear system whose solution minimizes
        // the quadric error associated with these two endpoints.
        
        // First we extract the upper-left 3x3 block of the 4x4
        // quadric error matrix.
        Matrix3x3 B;
        for( int i = 0; i < 3; i++ )
            for( int j = 0; j < 3; j++ )
            {
                B(i,j) = K(i,j);
            }
        
        // Next we extract the upper-right 3x1 vector of the
        // same quadric error matrix.
        Vector3D w;
        for( int i = 0; i < 3; i++ )
        {
            w[i] = -K(i,3);
        }
        
        // Using this system, we solve for the optimal position.
        Vector3D m = B.inv() * w;
        
        // The score associated with this edge is the quadric
        // error measured at the optimal position.
        Vector4D u( m.x, m.y, m.z, 1. );
        score = dot( K*u, u );
        
        // Store the optimal point.
        optimalPoint = m;
    }
    
    void MeshResampler::downsample( HalfedgeMesh& mesh )
    {
        // Our goal is to reduce the number of triangles by a factor of four,
        // which roughly corresponds to a doubling of the edge length (mirroring
        // the halving of edge length we get with Loop subdivision).
        const int targetFaceCount = mesh.nFaces() / 4;
        
        // Compute initial quadrics for each face by simply writing the plane
        // equation for the face in homogeneous coordinates.
        for( FaceIter f = mesh.facesBegin(); f != mesh.facesEnd(); f++ )
        {
            Vector3D N = f->normal();
            Vector3D p = f->halfedge()->vertex()->position;
            Vector4D u( N.x, N.y, N.z, -dot(N,p) );
            f->quadric = outer( u, u );
        }
        
        // Compute an initial quadric for each vertex as the sum of the quadrics
        // associated with the incident faces.
        for( VertexIter v = mesh.verticesBegin(); v != mesh.verticesEnd(); v++ )
        {
            Vector3D p = v->position;
            Vector4D q = Vector4D( p.x, p.y, p.z, 1. );
            
            v->quadric.zero();
            
            HalfedgeIter h = v->halfedge();
            do
            {
                v->quadric += h->face()->quadric;
                h = h->twin()->next();
            }
            while( h != v->halfedge() );
        }
        
        // Build a priority queue of edges according to their quadric error score.
        MutablePriorityQueue<EdgeRecord> edgeQueue;
        for( EdgeIter e = mesh.edgesBegin(); e != mesh.edgesEnd(); e++ )
        {
            e->record = EdgeRecord( e );
            edgeQueue.insert( e->record );
        }
        
        // Until we reach the target edge budget, collapse the best edge.
        while( mesh.nFaces() > targetFaceCount )
        {
            HalfedgeIter h;
            
            EdgeRecord r = edgeQueue.top();
            EdgeIter e = r.edge;
            
            VertexIter v0 = e->halfedge()->vertex();
            VertexIter v1 = e->halfedge()->twin()->vertex();
            
            h = v0->halfedge();
            do
            {
                EdgeIter ei = h->edge();
                if( ei != e )
                {
                    edgeQueue.remove( ei->record );
                }
                h = h->twin()->next();
            }
            while( h != v0->halfedge() );
            
            h = v1->halfedge();
            do
            {
                EdgeIter ei = h->edge();
                if( ei != e )
                {
                    edgeQueue.remove( ei->record );
                }
                h = h->twin()->next();
            }
            while( h != v1->halfedge() );
            
            Matrix4x4 K0 = v0->quadric;
            Matrix4x4 K1 = v1->quadric;
            
            VertexIter v = mesh.collapseEdge( e );
            v->position = r.optimalPoint;
            v->quadric = K0 + K1;
            
            h = v->halfedge();
            do
            {
                EdgeIter e = h->edge();
                e->record = EdgeRecord( e );
                edgeQueue.insert( e->record );
                
                h = h->twin()->next();
            }
            while( h != v->halfedge() );
            
            edgeQueue.pop();
        }
        mesh.initializeVertices();
    }
    
    void Vertex::computeCentroid( void )
    {
        centroid = Vector3D( 0., 0., 0. ); // centroid
        double d = 0.; // degree (i.e., number of neighbors)
        
        // Iterate over neighbors.
        HalfedgeCIter h = halfedge();
        do
        {
            // Add the contribution of the neighbor,
            // and increment the number of neighbors.
            centroid += h->next()->vertex()->position;
            d += 1.;
            
            h = h->twin()->next();
        }
        while( h != halfedge() );
        
        centroid /= d; // Compute the average, which is now stored in the member variable Vertex::centroid
    }
    
    Vector3D Vertex::normal(void) const {
        Vector3D normal = Vector3D( 0., 0., 0. );
        Vector3D pi = position;
        
        // Iterate over neighbors.
        HalfedgeCIter h = halfedge();
        if (isBoundary()) {
            do {
                Vector3D pj = h->next()->vertex()->position;
                Vector3D pk = h->next()->next()->vertex()->position;
                normal += cross( pj-pi, pk-pi );
                h = h->next()->twin();
            } while( h != halfedge() );
        } else {
            do {
                Vector3D pj = h->next()->vertex()->position;
                Vector3D pk = h->next()->next()->vertex()->position;
                normal += cross( pj-pi, pk-pi );
                h = h->twin()->next();
            } while( h != halfedge() );
        }
        
        normal.normalize();
        return normal;
    }
    
    void MeshResampler::resample( HalfedgeMesh& mesh )
    {
        const int nIterations = 5;
        const int nSmoothingIterations = 20;
        EdgeIter e;
        
        // Compute the mean edge length; this will be the target length for remeshing.
        double meanEdgeLength = 0.;
        for( e = mesh.edgesBegin(); e != mesh.edgesEnd(); e++ )
        {
            meanEdgeLength += e->length();
        }
        meanEdgeLength /= (double) mesh.nEdges();
        meanEdgeLength *= .9;
        const double maxLength = meanEdgeLength * 4./3.;
        const double minLength = meanEdgeLength * 4./5.;
        
        for( int iteration = 0; iteration < nIterations; iteration++ )
        {
            // We first try to get more uniform edge lengths by splitting edges longer
            // than the threshold and collapsing edges shorter than the threshold.
            e = mesh.edgesBegin();
            while( e != mesh.edgesEnd() )
            {
                double length = e->length();
                
                // After splitting or collapsing, the current edge may no longer
                // exist; therefore, we need to grab a pointer to the next edge NOW.
                EdgeIter nextEdge = e;
                nextEdge++;
                
                if( length > maxLength ) // Split edges that are longer than the target length.
                {
                    mesh.splitEdge( e );
                }
                
                e = nextEdge;
            }
            
            // We first try to get more uniform edge lengths by splitting edges longer
            // than the threshold and collapsing edges shorter than the threshold.
            e = mesh.edgesBegin();
            while( e != mesh.edgesEnd() )
            {
                double length = e->length();
                
                // After splitting or collapsing, the current edge may no longer
                // exist; therefore, we need to grab a pointer to the next edge NOW.
                EdgeIter nextEdge = e;
                nextEdge++;
                
                if( length < minLength ) // Collapse edges that are shorter than the target length.
                {
                    // Collapsing an edge may invalidate not only this edge, but
                    // also any of the four edges in its immediate neighborhood.
                    // Therefore, we will advance the next edge to the first edge
                    // that is NOT one of these edges.
                    EdgeIter e1 = e->halfedge()->next()->edge();
                    EdgeIter e2 = e->halfedge()->next()->next()->edge();
                    EdgeIter e3 = e->halfedge()->twin()->next()->edge();
                    EdgeIter e4 = e->halfedge()->twin()->next()->next()->edge();
                    while( nextEdge == e  ||
                          nextEdge == e1 ||
                          nextEdge == e2 ||
                          nextEdge == e3 ||
                          nextEdge == e4 )
                    {
                        nextEdge++;
                    }
                    
                    // Now we can safely collapse the edge.
                    mesh.collapseEdge( e );
                }
                
                e = nextEdge;
            }
            
            // Next, we flip edges in an effort to get more uniform vertex valence.
            e = mesh.edgesBegin();
            while( e != mesh.edgesEnd() )
            {
                // After flipping, the current edge may no longer exist; therefore,
                // we need to grab a pointer to the next edge NOW.  (In principle,
                // one could implement edge flip such that the flipped edge is
                // not destroyed; however, we will not make that assumption here
                // for the sake of safety/robustness to future changes in the method
                // that performs the flipping.)
                EdgeIter nextEdge = e;
                nextEdge++;
                
                int a0 = e->halfedge()->vertex()->degree();
                int a1 = e->halfedge()->twin()->vertex()->degree();
                int b0 = e->halfedge()->next()->next()->vertex()->degree();
                int b1 = e->halfedge()->twin()->next()->next()->vertex()->degree();
                if( a0 != 3 && a1 != 3 && b0 != 3 && b1 != 3 )
                {
                    int oldDefect = abs( a0-6 ) + abs( a1-6 ) + abs( b0-6 ) + abs( b1-6 );
                    int newDefect = abs( (a0-1)-6 ) + abs( (a1-1)-6 ) + abs( (b0+1)-6 ) + abs( (b1+1)-6 );
                    
                    if( newDefect < oldDefect && a0-1 > 3 && a1-1 > 3 )
                    {
                        mesh.flipEdge( e );
                    }
                }
                
                e = nextEdge;
            }
            
            // Finally, we apply some tangential smoothing, to improve the shape
            // of the triangles.
            for( int i = 0; i < nSmoothingIterations; i++ )
            {
                // First, we compute the centroids of each vertex (i.e., the average
                // of its neighbors' positions).
                for( VertexIter v = mesh.verticesBegin(); v != mesh.verticesEnd(); v++ )
                {
                    v->computeCentroid();
                }
                
                // Next, we move the vertex in a tangential direction toward its centroid.
                for( VertexIter v = mesh.verticesBegin(); v != mesh.verticesEnd(); v++ )
                {
                    Vector3D N = v->normal();
                    Vector3D p = v->position;
                    Vector3D c = v->centroid;
                    
                    Vector3D u = .5*(c-p);
                    u -= dot( u, N )*N;
                    
                    v->position += u;
                }
            }
        }
        mesh.initializeVertices();
    }
}
