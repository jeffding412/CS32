void listAll(const Class* c, string path)
{
    if (! path.empty())
        path += "=>";
    path += c->name();
    cout << path << endl;
    for (size_t k = 0; k != c->subclasses().size(); k++)
	listAll(c->subclasses()[k], path);
}
