{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "addon.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
		"..\\eigen-eigen-10219c95fe65\\"
      ]
    }
  ]
}
