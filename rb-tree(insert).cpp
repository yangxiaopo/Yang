//���ֲ��ĵ����϶Ժ�����Ľ����һ����������.��������(��):
//
//�������ÿ���ڵ㶼������ɫ���ԵĶ������������ɫΪ��ɫ���ɫ���ڶ��������ǿ��һ��Ҫ�����⣬�����κ���Ч�ĺ�����������������µĶ���Ҫ��
//  1.�ڵ��Ǻ�ɫ���ɫ��
//    2.���Ǻ�ɫ��
//    3.����Ҷ�Ӷ��Ǻ�ɫ��NULL��Ϊ�գ���
//    4.ÿ����ɫ�ڵ������������ɫ���ӽڵ㡣����ÿ��Ҷ�ӵ���������·���ϲ��������������ĺ�ɫ�ڵ㡣��
//    5.����һ�ڵ㵽��ÿ��Ҷ�ӵ����м�·����������ͬ��Ŀ�ĺ�ɫ�ڵ㡣
//    ���ݹ���4,�����ڵ����Ϊ��ɫ;
//    �涨һ��,Ҫ����Ľڵ��ΪN��N�ĸ��ڵ��ΪP��N���游�ڵ��ΪG��N���常�ڵ��ΪU
//    ���¼���PΪG��������,�������ԳƲ�������

//�������2-3-4����һ�ֵ�ͬ.��2-3-4���ϵĲ����ɾ������Ҳ��ͬ���ں��������ɫ��ת����ת.����2-3-4����ʵ���в�����ʹ�á����ϱ�
//
//                                               ����(insert)
//                                                     |
//���ڲ���ڵ�ĸ��ڵ�(P)Ϊ��ɫʱ,��Ӱ����������,END------����ڵ�ĸ��ڵ�(P)Ϊ��ɫʱ�����ڲ���֮ǰ����һ�������,G���Ǻ�ɫ
//																					|
//		                                                  ��ôUΪ��ɫ------------------------------------UΪ��ɫ
//												                  |										      |
//                                               NΪP�������� <-------NΪP��������				NΪP��������-------->NΪP��������
//												 P,G����,��ɫEND      N,P����(ת��Ϊ������)     N,P����              P,G����,N���(G��ʱΪ��)
//																															|
//																									��G�ĸ��ڵ�Ϊ��.END-------��G�ĸ��ڵ�Ϊ�죬�����ƻ�,
//																															  �轫G��Ϊ����ڵ�N���ϵ�����,�ص���ʼ
//												         


//1.���ұߵ��������P,N,UΪ��,GΪ�ڵ������������ת��ɫ�Ľ����������һ���ģ�
//	GΪ��Ϊ��ɫ,2���ֽڵ��Ϊ��ɫ.(�˷����������ʡ�ڴ�SGI STL������ô�ɵģ�����������ԭ��׸��)
//2.���仰˵,����ڵ�Ϊ����������������Ӱ��,ͨ��һ����ת�Ϳ����໥ת��.ֻ��Ҫ��2�������p,Nͬɫ/��ɫ
//  ��ͬɫ����1,��ɫ��תEND
//3.��ƪ ɾ��ͬ����
//
//�Դ�,�������������SGI STLԴ��


inline void 
_Rb_tree_rebalance(_Rb_tree_node_base* __x, _Rb_tree_node_base*& __root)
{
  __x->_M_color = _S_rb_tree_red;//�¼���Ľڵ����Ϊ��(���������)
  while (__x != __root && __x->_M_parent->_M_color == _S_rb_tree_red) { //���ǿ������߲���ڵ�ĸ��ڵ�Ϊ��ɫʱ.
    if (__x->_M_parent == __x->_M_parent->_M_parent->_M_left) {
      _Rb_tree_node_base* __y = __x->_M_parent->_M_parent->_M_right;
      if (__y && __y->_M_color == _S_rb_tree_red) { //(��ڵ�Ϊ��ʱ)ĳ�ڵ�X��2���ӽڵ㶼Ϊ��ʱ,��2���ӽڵ����ɫ��Ϊ��,X��Ϊ��,ѭ��֪�����ڵ����Ϻ��������.
        __x->_M_parent->_M_color = _S_rb_tree_black;
        __y->_M_color = _S_rb_tree_black;
        __x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;
        __x = __x->_M_parent->_M_parent;
      }
      else {
        if (__x == __x->_M_parent->_M_right) { //�常�ڵ�Ϊ��ɫʱ,����(����)����һ������(����),����Ϊ����(����).
          __x = __x->_M_parent;
          _Rb_tree_rotate_left(__x, __root);
        }
        __x->_M_parent->_M_color = _S_rb_tree_black;
        __x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;
        _Rb_tree_rotate_right(__x->_M_parent->_M_parent, __root);
      }
    }
    else {//�Գ��෴�Ĳ���
      _Rb_tree_node_base* __y = __x->_M_parent->_M_parent->_M_left;
      if (__y && __y->_M_color == _S_rb_tree_red) {
        __x->_M_parent->_M_color = _S_rb_tree_black;
        __y->_M_color = _S_rb_tree_black;
        __x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;
        __x = __x->_M_parent->_M_parent;
      }
      else {
        if (__x == __x->_M_parent->_M_left) {
          __x = __x->_M_parent;
          _Rb_tree_rotate_right(__x, __root);
        }
        __x->_M_parent->_M_color = _S_rb_tree_black;
        __x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;
        _Rb_tree_rotate_left(__x->_M_parent->_M_parent, __root);
      }
    }
  }
  __root->_M_color = _S_rb_tree_black;
}