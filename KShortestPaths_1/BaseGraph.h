///////////////////////////////////////////////////////////////////////////////
///  BaseGraph.h
///  <TODO: insert file description here>
///
///  @remarks <TODO: insert remarks here>
///
///  @author Yan Qi @date 6/6/2010
///
///  $Id$
///
///////////////////////////////////////////////////////////////////////////////

#pragma once

class BaseGraph
{
public: // members

	const static double DISCONNECT; 

	typedef typename set<BaseVertex*>::iterator VertexPtSetIterator;
	typedef typename map<BaseVertex*, set<BaseVertex*>*>::iterator BaseVertexPt2SetMapIterator;

protected: // members

	map<BaseVertex*, set<BaseVertex*>*> m_mpFanoutVertices;
	map<BaseVertex*, set<BaseVertex*>*> m_mpFaninVertices;
	map<int, double> m_mpEdgeCodeWeight; 
	vector<BaseVertex*> m_vtVertices;
	int m_nEdgeNum;
	int m_nVertexNum;


public: // methods

	virtual ~BaseGraph(void){clear();}

	void clear();

protected: // methods

	int get_edge_code(const BaseVertex* start_vertex_pt, const BaseVertex* end_vertex_pt) const
	{
		/// Note that the computation below works only if 
		/// the result is smaller than the maximum of an integer!
		return start_vertex_pt->getID()*m_nVertexNum+end_vertex_pt->getID();
	}

public: 

	double get_edge_weight(const BaseVertex* start_vertex_pt, const BaseVertex* end_vertex_pt) const
	{
		map<int, double>::const_iterator pos = 
			m_mpEdgeCodeWeight.find(get_edge_code(start_vertex_pt, end_vertex_pt));

		if (pos != m_mpEdgeCodeWeight.end())
		{
			return pos->second;
		}

		return DISCONNECT;
	}

	BaseVertex* get_vertex_by_ID(int id) const
	{
		return m_vtVertices.at(id);
	}

	set<BaseVertex*>* get_precedent_vertex_set(BaseVertex* vertex) 
	{
		return get_vertex_set_pt(vertex, m_mpFaninVertices);
	}

	set<BaseVertex*>* get_adjacent_vertex_set(BaseVertex* vertex) 
	{
		return get_vertex_set_pt(vertex, m_mpFanoutVertices);
	}

	set<BaseVertex*>* get_vertex_set_pt(BaseVertex* vertex_, 
		map<BaseVertex*, set<BaseVertex*>*>& vertex_container_index)
	{
		BaseVertexPt2SetMapIterator pos = vertex_container_index.find(vertex_);

		if(pos == vertex_container_index.end())
		{
			set<BaseVertex*>* vertex_set = new set<BaseVertex*>();
			pair<BaseVertexPt2SetMapIterator,bool> ins_pos = 
				vertex_container_index.insert(make_pair(vertex_, vertex_set));

			pos = ins_pos.first;
		}

		return pos->second;
	}
};
