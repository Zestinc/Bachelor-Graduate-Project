jQuery(function () {
    // 6 create an instance when the DOM is ready
    jQuery('#jstree').jstree({
      "core" : {
        "multiple" : false,
        "animation" : 0
    }
});
    // 7 bind to events triggered on the tree
    jQuery('#jstree').on("changed.jstree", function (e, data) {
    	// console.log(data.selected);
    });
    jQuery('#jstree').on("select_node.jstree", function(e, data){
    	console.log(data.instance.get_node(data.selected).text);
        //调用js函数处理获得的node的text
        handle_selected(data.instance.get_node(data.selected).text);
    });
})
// .jstree();