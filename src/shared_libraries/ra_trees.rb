# -*- coding: utf-8 -*-
# 
# Author: José Emiliano Cabrera Blancas (jemiliano.cabrera@gmail.com)
#
require 'ffi'

require File.expand_path(File.join(File.dirname(__FILE__),"double_linked_list"))
require File.expand_path(File.join(File.dirname(__FILE__),"points"))
require File.expand_path(File.join(File.dirname(__FILE__),"rb_trees"))


#
# Modulo para mapear los range-tree de C a Ruby, junto con sus funciones.
#
module RATree
  extend FFI::Library
  ffi_lib "lib/librange_tree.so"
  
  class Tree < FFI::Struct
    layout :root, :pointer
  end

  attach_function :init_ra_tree, [], Tree.by_ref
  attach_function :destroy_rb_tree, [Tree.by_ref], :void

  attach_function :build_2d_range_tree, [List::List.by_ref], Tree.by_ref
  attach_function :two_d_range_query, [Tree.by_ref, :double, :double,
                                       :double, :double], List::List.by_ref
end
