var consts = {SHAREOBJ_ID: 'XRT123'};
var shareObj = { id1: '#val_id1', id2: { id21: '#val_id21', id22: '#val_id22' }, id3: '#val_id3' };
var recievedObj = {};

function storeInLocalStorage() {    
    localStorage.setItem( consts.SHAREOBJ_ID, JSON.stringify( shareObj ) );
    recievedObj = JSON.parse( localStorage.getItem( consts.SHAREOBJ_ID ) );
    console.log(JSON.stringify(recievedObj));
}


