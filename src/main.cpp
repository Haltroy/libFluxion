/*
    In this example, we are going to do the following (in order):
    1) Create some information
    2) Store the information
    3) Read the information
    4) Compare the saved information with the current information
*/

// In order to use Fluxion, we should include the required header.
// Since our application is in the same directory as the library itself,
// we can just include them here like this.
// Usually you would include them with #include <Fluxion>
#include "shared/Fluxion.h"
#include "shared/FluxionNode.h"
#include "shared/DataValues.h"
#include <iostream>

// Let's set up our program's main call.
int main(int argc, char const *argv[]) {
    // For our example, let's use this encoding. You can change it to any other encoding if you desire.
    const auto encoding = new UTF8Encoding();

    // Let's create a node that we will treat like a root node.
    // (Just like <root> on XML). And we will name it "MyRootNode".
    auto root = new FluxionNode(nullptr, "MyRootNode", new NullValue);

    // Let's create a new node and add it to our root node.
    auto node1 = new FluxionNode(root, "User", new StringValue("mike"));

    // Let's add some attribute o our node.
    auto node1_attr1 = new FluxionAttribute("Age", new IntValue(35));

    // You can use node1->Attributes.begin() to insert it to the start instead.
    // This will add it to the end of it.
    node1->Attributes.insert(node1->Attributes.end(), node1_attr1);

    // Let's add our node to the root.
    root->Add(node1);

    // Let's create another user and add it to the node instead this time.
    auto node1_1 = new FluxionNode(node1, "User", new StringValue("jeremy"));
    auto node1_1_attr1 = new FluxionAttribute("Age", new IntValue(10));
    node1_1->Attributes.insert(node1_1->Attributes.end(), node1_1_attr1);
    node1->Add(node1_1);

    // Let's save it to a file.
    Fluxion::Write(root, "test.flx", encoding);

    // Let's read it back.
    auto read_root = Fluxion::Read("test.flx");

    // Compare what we read with our own data.
    if (root->Name == read_root->Name && root->Value && read_root->Value) {
        std::cout << "Roots are same \n";
    }

    // And finally, exit the program.
    return 0;
}
