/// https://hackingcpp.com/cpp/std/special_iterators.html

// Container Manipulators
// 		std::insert_iterator<Container> 
// 		std::back_insert_iterator<Container> 
// 		std::front_insert_iterator<Container> 
// I/O Stream Iterators
// 		std::ostream_iterator<ValueType> 
// 		std::istream_iterator<ValueType> 
// Standard Algorithm Compatibility
		// The following tables list standard algorithms that are compatible with the special iterators presented above.

		// Since the special iterators are only input or output iterators they cannot be used with algorithms that require forward, bidirectional or random access iterators.

// 		Copying
// 			copy	In	Out
// 			copy_n	In	Out
// 			copy_if	In	Out
// 			sample	In	Out
// 		Changing Elements
// 			transform	In	Out
// 			replace_copy	In	Out
// 			replace_copy_if	In	Out
// 			fill_n	—	Out
// 			generate_n	—	Out
// 		Querying
// 			all_of	In	—
// 			any_of	In	—
// 			none_of	In	—
// 			count	In	—
// 			count_if	In	—
// 		Reordering
// 			rotate_copy	In	Out
// 			reverse_copy	In	Out
// 			partial_sort_copy	In	Out
// 			partition_copy	In	Out
// 			is_partitioned	In	—
// 		Removing
// 			remove_copy	In	Out
// 			remove_copy_if	In	Out
// 			unique_copy	In	Out
// 		Finding
// 			find	In	—
// 			find_if	In	—
// 			find_if_not	In	—
// 			find_first_of	In	—
// 		Comparing
// 			equal	In	—
// 			mismatch	In	—
// 			lexicographical_compare	In	—
// 			lexicographical_compare_three_way	In	—
// 		Traversal
// 			for_each	In	—
// 			for_each_n	In	—
// 		Sorted Sequence Operations
// 			includes	In	—
// 			merge	In	Out
// 			set_difference	In	Out
// 			set_intersection	In	Out
// 			set_union	In	Out
// 			set_symmetric_difference	In	Out
// 		Numeric Operations
// 			accumulate	In	—
// 			adjacent_difference	In	Out
// 			exclusive_scan	In	Out
// 			inclusive_scan	In	Out
// 			inner_product	In	—
// 			partial_sum	In	Out
// 			reduce	In	—
// 			transform_exclusive_scan	In	Out
// 			transform_inclusive_scan	In	Out
// 			transform_reduce	In	—
